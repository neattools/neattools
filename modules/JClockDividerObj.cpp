#include "JClockDividerObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JMath.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJClockDividerObj = JClockDividerObj().Register();
void JClockDividerObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "N", N);
  putInteger(os, "ivalue", ivalue);
}

void JClockDividerObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  N = getInteger(dict, "N");
  ivalue = getInteger(dict, "ivalue");
  ogm = N+1;
}

const char* JClockDividerObj::className() const { return "JClockDividerObj";}
JObject* JClockDividerObj::clone() const { return new JClockDividerObj(*this);}

JClockDividerObj::JClockDividerObj() {
  N = 2;
  igm = IN_LAST;
  ogm = N+1;
  ivalue = 0;
  reset = 0;
}

void JClockDividerObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CkDiv"), rect);
}

void JClockDividerObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = (!n) ? value : (value == n-1);}

boolean JClockDividerObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JClockDividerObj::inputTag(int n) {
  char* tag[] = { "clock(logical)", "N(2-512)", "reset(logical)"};
  return tag[n];
}

JString JClockDividerObj::outputTag(int n) {
  if (!n) return JString("value");
  return JString("out-")+JInteger::toJString(n-1)+NBTag();
}

JFRect JClockDividerObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, IN_LAST-1);
}

JFRect JClockDividerObj::outputArea(int n) {
  if (!n) return bottomArea(n, 0, 1);
  return rightArea(n, 1, N, 0, 1);
}

int JClockDividerObj::outputFace(int n) {
  if (!n) return BOTTOM;
  return RIGHT;
}

JFPoint JClockDividerObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, IN_LAST-1);
}

JFPoint JClockDividerObj::outputPoint(int n, JLinkObj& link) {
  if (!n) return bottomPoint(n, link, 0, 1);
  return rightPoint(n, link, 1, N, 0, 1);
}

void JClockDividerObj::engine(int n, JLinkObj& link) {
  if (n == IN_DATA) {
    int oldv = ivalue;
    link.access(JIntegerData(ivalue));
    if ((oldv != ivalue) && ivalue)
      updateValue(value+1);
  } else if (n == IN_N) {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else if (n == IN_RESET) {
    int oldv = reset;
    link.access(JIntegerData(reset));
    if ((oldv != reset) && reset)
      updateValue(0);
  }
}

JArray JClockDividerObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 512));
  return properties;
}

boolean JClockDividerObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  }
  return false;
}

void JClockDividerObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateOutputUpdate();
  N = max(2, min(512, _N));
  if (N != oldv) {
    ogm = N+1;
    updateValue(0);
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}

void JClockDividerObj::updateValue(int _value) {
  int oldv = value;
  value = _value % N;
  broadcast(oldv+1);
  broadcast(value+1);
  broadcast(0);
}