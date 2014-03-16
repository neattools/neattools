#include "JSDelObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JStringData.h"

char* theJSDelObj = JSDelObj().Register();

void JSDelObj::writeContent(JOutputStream& os) {
  JSAddObj::writeContent(os);
  putInteger(os, "from", from);
}

void JSDelObj::readContent(JDictionary& dict) {
  JSAddObj::readContent(dict);
  from = getInteger(dict, "from");
}

const char* JSDelObj::className() const { return "JSDelObj";}
JObject* JSDelObj::clone() const { return new JSDelObj(*this);}
JSDelObj::JSDelObj() { igm = IN_LAST; from = 0; to = -1;}
boolean JSDelObj::inputAllowed(int n) { return !inputSet(n).last();}

int JSDelObj::inputType(int n) {
  if (n < IN_FROM) return JStringData::id;
  return JIntegerData::id;
}

JString JSDelObj::inputTag(int n) {
  char* tag[] = { "input", "from", "to"};
  return tag[n];
}

JFRect JSDelObj::inputArea(int n) {
  if (n < IN_FROM) return leftArea(n, 0, IN_FROM);
  return topArea(n, IN_FROM, IN_LAST-IN_FROM);
}

JFPoint JSDelObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_FROM) return leftPoint(n, link, 0, IN_FROM);
  return topPoint(n, link, IN_FROM, IN_LAST-IN_FROM);
}

void JSDelObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Del"), rect);
}

void JSDelObj::putResult() {
  JString ov = value;
  int dest = to;
  int sz = str.length();
  if (sz > 0) {
    from = max(0, min(sz-1, from));
    if (inputSet(IN_TO).last()) {
      if (dest < 0) dest = sz;
      else dest = max(from, min(sz, dest));
    } else dest = from+1;
    value = str(0, from)+str(dest);
  } else value = str;
  if (value != ov) broadcast(0);
}

void JSDelObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JString ov = str;
      link.access(JStringData(str));
      if (str != ov) putResult();
      break;
    }
    case IN_FROM: {
      int ov = from;
      link.access(JIntegerData(from));
      if (from != ov) putResult();
      break;
    }
    case IN_TO: {
      int ov = to;
      link.access(JIntegerData(to));
      if (to != ov) putResult();
      break;
    }
  }
}
