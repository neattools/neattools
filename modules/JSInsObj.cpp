#include "JSInsObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JStringData.h"

char* theJSInsObj = JSInsObj().Register();

void JSInsObj::writeContent(JOutputStream& os) {
  JSAddObj::writeContent(os);
  putInteger(os, "pos", pos);
}

void JSInsObj::readContent(JDictionary& dict) {
  JSAddObj::readContent(dict);
  pos = getInteger(dict, "pos");
}

const char* JSInsObj::className() const { return "JSInsObj";}
JObject* JSInsObj::clone() const { return new JSInsObj(*this);}
JSInsObj::JSInsObj() { igm = IN_LAST; pos = 0;}
boolean JSInsObj::inputAllowed(int n) { return !inputSet(n).last();}

int JSInsObj::inputType(int n) {
  if (n < IN_POS) return JStringData::id;
  return JIntegerData::id;
}

int JSInsObj::inputFace(int n) {
  if (n < IN_POS) return LEFT;
  return TOP;
}

JString JSInsObj::inputTag(int n) {
  char* tag[] = { "input", "source", "pos"};
  return tag[n];
}

JFRect JSInsObj::inputArea(int n) {
  if (n < IN_POS) return leftArea(n, 0, IN_POS);
  return topArea(n, IN_POS,  IN_LAST-IN_POS);
}

JFPoint JSInsObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_POS) return leftPoint(n, link, 0, IN_POS);
  return topPoint(n, link, IN_POS, IN_LAST-IN_POS);
}

void JSInsObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Ins"), rect);
}

void JSInsObj::putResult() {
  JString ov = value;
  int sz = str.length();
  pos = max(0, min(sz, pos));
  value = str.insertAt(src, pos);
  if (value != ov) broadcast(0);
}

void JSInsObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JString ov = str;
      link.access(JStringData(str));
      if (str != ov) putResult();
      break;
    }
    case IN_SRC: {
      JString ov = src;
      link.access(JStringData(src));
      if (src != ov) putResult();
      break;
    }
    case IN_POS: {
      int ov = pos;
      link.access(JIntegerData(pos));
      if (pos != ov) putResult();
      break;
    }
  }
}
