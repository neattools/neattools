#include "JBInsObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBytesData.h"

char* theJBInsObj = JBInsObj().Register();

void JBInsObj::writeContent(JOutputStream& os) {
  JBAddObj::writeContent(os);
  putInteger(os, "pos", pos);
}

void JBInsObj::readContent(JDictionary& dict) {
  JBAddObj::readContent(dict);
  pos = getInteger(dict, "pos");
}

const char* JBInsObj::className() const { return "JBInsObj";}
JObject* JBInsObj::clone() const { return new JBInsObj(*this);}
JBInsObj::JBInsObj() { igm = IN_LAST; pos = 0;}
boolean JBInsObj::inputAllowed(int n) { return !inputSet(n).last();}

int JBInsObj::inputType(int n) {
  if (n < IN_POS) return JBytesData::id;
  return JIntegerData::id;
}

int JBInsObj::inputFace(int n) {
  if (n < IN_POS) return LEFT;
  return TOP;
}

JString JBInsObj::inputTag(int n) {
  char* tag[] = { "input", "source", "pos"};
  return tag[n];
}

JFRect JBInsObj::inputArea(int n) {
  if (n < IN_POS) return leftArea(n, 0, IN_POS);
  return topArea(n, IN_POS,  IN_LAST-IN_POS);
}

JFPoint JBInsObj::inputPoint(int n, JLinkObj& link) {
  if (n < IN_POS) return leftPoint(n, link, 0, IN_POS);
  return topPoint(n, link, IN_POS, IN_LAST-IN_POS);
}

void JBInsObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Ins"), rect);
}

void JBInsObj::putResult() {
  JString ov = value;
  int sz = blk.size();
  pos = max(0, min(sz, pos));
  value = blk.insertAt(src, pos);
  if (value != ov) broadcast(0);
}

void JBInsObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      JBlock ov = blk;
      link.access(JBytesData(blk));
      if (blk != ov) putResult();
      break;
    }
    case IN_SRC: {
      JBlock ov = src;
      link.access(JBlockData(src));
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
