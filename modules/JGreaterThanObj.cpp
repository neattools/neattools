#include "JGreaterThanObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJGreaterThanObj = JGreaterThanObj().Register();
void JGreaterThanObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "v0", v[0]);
  putInteger(os, "v1", v[1]);
}

void JGreaterThanObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  v[0] = getInteger(dict, "v0");
  v[1] = getInteger(dict, "v1");
}

const char* JGreaterThanObj::className() const { return "JGreaterThanObj";}
JObject* JGreaterThanObj::clone() const { return new JGreaterThanObj(*this);}
JGreaterThanObj::JGreaterThanObj() 
{ igm = 2; v[0] = v[1] = 0;}

void JGreaterThanObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx*3, x+bx};
  int yy[] = { y+by+dy*2, y+by+dy, y+by};
  g.drawPolygon(xx, yy, 3);
}

JString JGreaterThanObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JGreaterThanObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  value = (v[0] > v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

