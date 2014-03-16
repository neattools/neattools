#include "JDecoderObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJDecoderObj = JDecoderObj().Register();
void JDecoderObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
}

void JDecoderObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  ogm = N;
}

const char* JDecoderObj::className() const { return "JDecoderObj";}
JObject* JDecoderObj::clone() const { return new JDecoderObj(*this);}

JDecoderObj::JDecoderObj() {
 igm = 2;
  ogm = N = 2;
}

void JDecoderObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = ((value & (1 << n)) != 0);}

void JDecoderObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Dec"), rect);
}

boolean JDecoderObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JDecoderObj::inputTag(int n) {
  char* tag[] = {"input", "N(2-32)"};
  return tag[n];
}

JString JDecoderObj::outputTag(int n) {
  return JString("out-")+JInteger::toJString(n)+"(logical)";
}

JFRect JDecoderObj::outputArea(int n) 
{ return rightArea(n, 0, N, 0, 1);}

JFPoint JDecoderObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, N, 0, 1);}

void JDecoderObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int oldv = value;
    link.access(JIntegerData(value));
    if (value != oldv) {
      for (int i=0; i<N; i++) {
        int mask = 1<<i;
        if ((oldv & mask) != (value & mask)) 
	  broadcast(i);
      }
    }
  } else {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  }
}

JArray JDecoderObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 32));
  return properties;
}

boolean JDecoderObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

void JDecoderObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateOutputUpdate();
  N = max(2, min(32, _N));
  if (N != oldv) {
    ogm = N;
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}

