#include "JBDelObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBytesData.h"

char* theJBDelObj = JBDelObj().Register();

void JBDelObj::writeContent(JOutputStream& os) {
  JBAddObj::writeContent(os);
  putInteger(os, "from", from);
}

void JBDelObj::readContent(JDictionary& dict) {
  JBAddObj::readContent(dict);
  from = getInteger(dict, "from");
}

const char* JBDelObj::className() const { return "JBDelObj";}
JObject* JBDelObj::clone() const { return new JBDelObj(*this);}
JBDelObj::JBDelObj() { igm = IN_LAST; from = 0; to = -1;}
boolean JBDelObj::inputAllowed(int n) { return !inputSet(n).last();}

int JBDelObj::inputType(int n) {
  if (n < IN_FROM) return JBytesData::id;
  return JIntegerData::id;
}

JString JBDelObj::inputTag(int n) {
  char* tag[] = { "input", "from", "to"};
  return tag[n];
}

JFRect JBDelObj::inputArea(int n) {
  if (n < IN_FROM) return leftArea(n, 0, IN_FROM);
  return topArea(n, IN_FROM, IN_LAST-IN_FROM);
}

JFPoint JBDelObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_FROM) return leftPoint(n, link, 0, IN_FROM);
  return topPoint(n, link, IN_FROM, IN_LAST-IN_FROM);
}

void JBDelObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Del"), rect);
}

void JBDelObj::putResult() {
  JBlock ov = value;
  int dest = to;
  int sz = block.size();
  if (sz > 0) {
    from = max(0, min(sz-1, from));
    if (inputSet(IN_TO).last()) {
      if (dest < 0) dest = sz;
      else dest = max(from, min(sz, dest));
    } else dest = from+1;
    value = block(0, from)+block(dest);
  } else value = block;
  if (value != ov) broadcast(0);
}

void JBDelObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JString ov = block;
      link.access(JBytesData(block));
      if (block != ov) putResult();
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
