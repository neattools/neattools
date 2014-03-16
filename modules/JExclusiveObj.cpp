#include "JExclusiveObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJExclusiveObj = JExclusiveObj().Register();
void JExclusiveObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "N", N);
  putInteger(os, "select", select);
  putInteger(os, "trueEventOnly", trueEventOnly);
}

void JExclusiveObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  N = getInteger(dict, "N");
  select = getInteger(dict, "select");
  trueEventOnly = getInteger(dict, "trueEventOnly");
  ogm = N;
  igm = N+1;
}

const char* JExclusiveObj::className() const { return "JExclusiveObj";}
JObject* JExclusiveObj::clone() const { return new JExclusiveObj(*this);}

JExclusiveObj::JExclusiveObj() {
  N = 2;
  ogm = N;
  igm = N+1;
  trueEventOnly = false;
}

void JExclusiveObj::access(int n, JLinkObj& link, const JDataType& data)
{ INT(data) = (n == select) ? value : 0;}

void JExclusiveObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Exc"), rect);
}

boolean JExclusiveObj::inputAllowed(int n)
{ return (!n) ? !inputSet(n).last() : true;}

JString JExclusiveObj::inputTag(int n) {
  if (!n) return JString("N(2-32)");
  return JString("in-")+JInteger::toJString(n-1);
}

JString JExclusiveObj::outputTag(int n) 
{ return JString("out-")+JInteger::toJString(n);}

JFRect JExclusiveObj::inputArea(int n) {
  if (!n) return topArea(n, 0, 1);
  return leftArea(n, 1, N, 0, 1);
}

JFRect JExclusiveObj::outputArea(int n) 
{ return rightArea(n, 0, N, 0, 1);}

int JExclusiveObj::inputFace(int n) {
  if (!n) return TOP;
  return LEFT;
}

JFPoint JExclusiveObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return topPoint(n, link, 0, 1);
  return leftPoint(n, link, 1, N, 0, 1);
}

JFPoint JExclusiveObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, N, 0, 1);}

void JExclusiveObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int _N;
    link.access(JIntegerData(_N));
    updateN(_N);
  } else {
    int iv;
    link.access(JIntegerData(iv));
    if (select != n-1) {
      if (iv) {
        int oldsel = select;
        select = n-1;
        value = iv;
        broadcast(select);
        if (select != oldsel)
        broadcast(oldsel);
      }
    } else if (iv && trueEventOnly || !trueEventOnly) {
      value = iv;
      broadcast(select);
    }
  }
}

JArray JExclusiveObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("N", N, 2, 32));
  properties.append(JIntegerListProperty("trueEventOnly", trueEventOnly,
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JExclusiveObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("trueEventOnly")) {
    trueEventOnly = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

void JExclusiveObj::updateN(int _N) {
  int oldv = N;
  JFRect rect = calculateInputUpdate();
  rect |= calculateOutputUpdate();
  N = max(2, min(32, _N));
  if (N != oldv) {
    ogm = N;
    igm = N+1;
    rect |= calculateInputUpdate();
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}

