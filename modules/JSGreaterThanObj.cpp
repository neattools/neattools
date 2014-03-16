#include "JSGreaterThanObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSGreaterThanObj = JSGreaterThanObj().Register();
void JSGreaterThanObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putString(os, "v0", v[0]);
  putString(os, "v1", v[1]);
}

void JSGreaterThanObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  v[0] = getString(dict, "v0");
  v[1] = getString(dict, "v1");
}

const char* JSGreaterThanObj::className() const { return "JSGreaterThanObj";}
JObject* JSGreaterThanObj::clone() const { return new JSGreaterThanObj(*this);}
JSGreaterThanObj::JSGreaterThanObj() { 
  igm = 2;;
  moduleColor = JStringData::color;
}

void JSGreaterThanObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx*3, x+bx};
  int yy[] = { y+by+dy*2, y+by+dy, y+by};
  g.drawPolygon(xx, yy, 3);
}

int JSGreaterThanObj::inputType(int n) { return JStringData::id;}
JString JSGreaterThanObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JSGreaterThanObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JStringData(v[n]));
  value = (v[0] > v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

