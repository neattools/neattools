#include "JRGreaterThanObj.h"
#include "JLinkObj.h"
#include "JRealData.h"

char* theJRGreaterThanObj = JRGreaterThanObj().Register();
void JRGreaterThanObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putDouble(os, "v0", v[0]);
  putDouble(os, "v1", v[1]);
}

void JRGreaterThanObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  v[0] = getDouble(dict, "v0");
  v[1] = getDouble(dict, "v1");
}

const char* JRGreaterThanObj::className() const { return "JRGreaterThanObj";}
JObject* JRGreaterThanObj::clone() const { return new JRGreaterThanObj(*this);}
JRGreaterThanObj::JRGreaterThanObj() { 
  igm = 2; v[0] = v[1] = 0;
  moduleColor = JRealData::color;
}

void JRGreaterThanObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx*3, x+bx};
  int yy[] = { y+by+dy*2, y+by+dy, y+by};
  g.drawPolygon(xx, yy, 3);
}

int JRGreaterThanObj::inputType(int n) { return JRealData::id;}
JString JRGreaterThanObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JRGreaterThanObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JRealData(v[n]));
  value = (v[0] > v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

