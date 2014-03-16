#include "JCEqualObj.h"
#include "JLinkObj.h"
#include "JComplexData.h"

char* theJCEqualObj = JCEqualObj().Register();
void JCEqualObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putDouble(os, "real0", v[0].r);
  putDouble(os, "imag0", v[0].i);
  putDouble(os, "real1", v[1].r);
  putDouble(os, "imag1", v[1].i);
}

void JCEqualObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  v[0].r = getDouble(dict, "real0");
  v[0].i = getDouble(dict, "imag0");
  v[1].r = getDouble(dict, "real1");
  v[1].i = getDouble(dict, "imag1");
}

const char* JCEqualObj::className() const { return "JCEqualObj";}
JObject* JCEqualObj::clone() const { return new JCEqualObj(*this);}
JCEqualObj::JCEqualObj() { 
  igm = 2; v[0] = v[1] = 0;
  moduleColor = JComplexData::color;
}

void JCEqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy)/2;
  g.drawLine(x+bx, y+by, x+bx+dx*3, y+by);
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
}

int JCEqualObj::inputType(int n) { return JComplexData::id;}
JString JCEqualObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JCEqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JComplexData(v[n]));
  value = (v[0] == v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

