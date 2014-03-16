#include "JEncoderObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJEncoderObj = JEncoderObj().Register();
void JEncoderObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
}

void JEncoderObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  igm = N+1;
}

const char* JEncoderObj::className() const { return "JEncoderObj";}
JObject* JEncoderObj::clone() const { return new JEncoderObj(*this);}

JEncoderObj::JEncoderObj() {
  N = 2;
  igm = N+1;
}

void JEncoderObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Enc"), rect);
}

boolean JEncoderObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JEncoderObj::inputTag(int n) {
  if (!n) return JString("N(2-32)");
  return JString("in-")+JInteger::toJString(n-1)+"(logical)";
}

JFRect JEncoderObj::inputArea(int n) {
  if (!n) return topArea(n, 0, 1);
  return leftArea(n, 1, N, 0, 1);
}

int JEncoderObj::inputFace(int n) {
  if (!n) return TOP;
  return LEFT;
}

JFPoint JEncoderObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return topPoint(n, link, 0, 1);
  return leftPoint(n, link, 1, N, 0, 1);
}

void JEncoderObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else {
    int oldv = value;
    int mask = 1<<(n-1);
    int ivalue;
    link.access(JIntegerData(ivalue));
    if (ivalue != 0) value |= mask;
    else value &= ~mask;
    if (value != oldv) broadcast(0);
  }
}

JArray JEncoderObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 32));
  return properties;
}

boolean JEncoderObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

void JEncoderObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateInputUpdate();
  N = max(2, min(32, _N));
  if (N != oldv) {
    igm = N+1;
    value &= (1<<N)-1;
    rect |= calculateInputUpdate();
    repaintView(rect);
  }
}

