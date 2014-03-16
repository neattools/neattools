#include "JDGreaterThanObj.h"
#include "JLinkObj.h"
#include "JDateData.h"

char* theJDGreaterThanObj = JDGreaterThanObj().Register();
void JDGreaterThanObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "v0", (int)v[0]);
  putInteger(os, "v1", (int)v[1]);
}

void JDGreaterThanObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  v[0] = JDate(getInteger(dict, "v0"));
  v[1] = JDate(getInteger(dict, "v1"));
}

const char* JDGreaterThanObj::className() const { return "JDGreaterThanObj";}
JObject* JDGreaterThanObj::clone() const { return new JDGreaterThanObj(*this);}
JDGreaterThanObj::JDGreaterThanObj() { 
  igm = 2; v[0] = v[1] = JDate();
  moduleColor = JDateData::color;
}

void JDGreaterThanObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx*3, x+bx};
  int yy[] = { y+by+dy*2, y+by+dy, y+by};
  g.drawPolygon(xx, yy, 3);
}

int JDGreaterThanObj::inputType(int n) { return JDateData::id;}
JString JDGreaterThanObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JDGreaterThanObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JDateData(v[n]));
  value = (v[0] > v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

