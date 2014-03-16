#include "JSSubObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JStringData.h"

char* theJSSubObj = JSSubObj().Register();

void JSSubObj::writeContent(JOutputStream& os) {
  JSAddObj::writeContent(os);
  putInteger(os, "begin", begin);
}

void JSSubObj::readContent(JDictionary& dict) {
  JSAddObj::readContent(dict);
  begin = getInteger(dict, "begin");
}

const char* JSSubObj::className() const { return "JSSubObj";}
JObject* JSSubObj::clone() const { return new JSSubObj(*this);}
JSSubObj::JSSubObj() { igm = IN_LAST; begin = 0; end = -1;}
boolean JSSubObj::inputAllowed(int n) { return !inputSet(n).last();}

int JSSubObj::inputType(int n) {
  if (n < IN_BEGIN) return JStringData::id;
  return JIntegerData::id;
}

JString JSSubObj::inputTag(int n) {
  char* tag[] = { "input", "begin", "end"};
  return tag[n];
}

JFRect JSSubObj::inputArea(int n) {
  if (n < IN_BEGIN) return leftArea(n, 0, IN_BEGIN);
  return topArea(n, IN_BEGIN, IN_LAST-IN_BEGIN);
}

JFPoint JSSubObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_BEGIN) return leftPoint(n, link, 0, IN_BEGIN);
  return topPoint(n, link, IN_BEGIN, IN_LAST-IN_BEGIN);
}

void JSSubObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Sub"), rect);
}

void JSSubObj::putResult() {
  JString ov = value;
  int dest = end;
  int sz = str.length();
  if (sz > 0) {
    begin = max(0, min(sz-1, begin));
    if (inputSet(IN_END).last()) {
      if (dest < 0) dest = sz;
      else dest = max(begin, min(sz, dest));
    } else dest = begin+1;
    value = str(begin, dest);
  } else value = str;
  if (value != ov) broadcast(0);
}

void JSSubObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JString ov = str;
      link.access(JStringData(str));
      if (str != ov) putResult();
      break;
    }
    case IN_BEGIN: {
      int ov = begin;
      link.access(JIntegerData(begin));
      if (begin != ov) putResult();
      break;
    }
    case IN_END: {
      int ov = end;
      link.access(JIntegerData(end));
      if (end != ov) putResult();
      break;
    }
  }
}
