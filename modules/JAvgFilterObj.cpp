#include "JAvgFilterObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JMath.h"

char* theJAvgFilterObj = JAvgFilterObj().Register();
void JAvgFilterObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
}

void JAvgFilterObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  N = max(2, min(1024, N));
  initialize();
}

const char* JAvgFilterObj::className() const { return "JAvgFilterObj";}
JObject* JAvgFilterObj::clone() const { return new JAvgFilterObj(*this);}

JAvgFilterObj::JAvgFilterObj() {
  N = 10;
  tail = head = 0;
  data = null;
}

void JAvgFilterObj::startup() { initialize();}

void JAvgFilterObj::initialize() {
  tail = head = sum = 0;
  buf = JBlock(N*sizeof(int), 0);
  data = (int*)(char*)buf;
}

boolean JAvgFilterObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JAvgFilterObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("Avg"), rect1);
  drawText(g, "Filter", rect2);
}

void JAvgFilterObj::engine(int n, JLinkObj& link) {
  int iv, next = (++head)%N;  
  link.access(JIntegerData(iv));
  iv = JMath::iabs(iv);
  if (next == tail) {
    sum+=(iv-data[tail]);
    data[head=next] = iv;
    tail = (++tail)%N;
    value = sum/N;
  } else {
    data[head=next] = iv;
    sum+=iv;
    value = sum/((head+N-tail)%N);
  }
  broadcast(0);
}

JArray JAvgFilterObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 1024));
  return properties;
}

boolean JAvgFilterObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    N = ((JIntegerProperty*)&prop)->value;
    initialize();
    return true;
  }
  return false;
}

