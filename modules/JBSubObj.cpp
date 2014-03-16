#include "JBSubObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBytesData.h"

char* theJBSubObj = JBSubObj().Register();

void JBSubObj::writeContent(JOutputStream& os) {
  JBAddObj::writeContent(os);
  putObject(os, "block", block);
  putInteger(os, "begin", begin);
  putInteger(os, "end", end);
}

void JBSubObj::readContent(JDictionary& dict) {
  JBAddObj::readContent(dict);
  JObject *obj = getObject(dict, "block");
  if (obj) block = *(JBlock*)obj;
  begin = getInteger(dict, "begin");
  end = getInteger(dict, "end");
}

const char* JBSubObj::className() const { return "JBSubObj";}
JObject* JBSubObj::clone() const { return new JBSubObj(*this);}
JBSubObj::JBSubObj() { igm = IN_LAST; begin = 0; end = -1;}
boolean JBSubObj::inputAllowed(int n) { return !inputSet(n).last();}

int JBSubObj::inputType(int n) {
  if (n < IN_BEGIN) return JBytesData::id;
  return JIntegerData::id;
}

JString JBSubObj::inputTag(int n) {
  char* tag[] = { "input", "begin", "end"};
  return tag[n];
}

JFRect JBSubObj::inputArea(int n) {
  if (n < IN_BEGIN) return leftArea(n, 0, IN_BEGIN);
  return topArea(n, IN_BEGIN, IN_LAST-IN_BEGIN);
}

JFPoint JBSubObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_BEGIN) return leftPoint(n, link, 0, IN_BEGIN);
  return topPoint(n, link, IN_BEGIN, IN_LAST-IN_BEGIN);
}

void JBSubObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Sub"), rect);
}

void JBSubObj::putResult() {
  JBlock ov = value;
  int dest = end;
  int sz = block.size();
  if (sz > 0) {
    begin = max(0, min(sz-1, begin));
    if (inputSet(IN_END).last()) {
      if (dest < 0) dest = sz;
      else dest = max(begin, min(sz, dest));
    } else dest = begin+1;
    value = block(begin, dest);
  } else value = block;
  if (value != ov) broadcast(0);
}

void JBSubObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JBlock ov = block;
      link.access(JBytesData(block));
      if (block != ov) putResult();
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
