#include "JCPolrObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"
#include "JComplexData.h"

char* theJCPolrObj = JCPolrObj().Register();

void JCPolrObj::readContent(JDictionary& dict) {
  JCtoRObj::readContent(dict);
  v[0] = value.abs();
  v[1] = value.arg();
}

const char* JCPolrObj::className() const { return "JCPolrObj";}
JObject* JCPolrObj::clone() const { return new JCPolrObj(*this);}

void JCPolrObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CPolr"), rect);
}

JString JCPolrObj::outputTag(int n) { 
  char* tag[] = { "R", "Theta"};
  return tag[n];
}

void JCPolrObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JComplexData(value));
  if (value != oldv) {
    v[0] = value.abs();
    v[1] = value.arg();
    broadcast(0);
    broadcast(1);
  }
}
