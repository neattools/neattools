#include "JRDivideObj.h"
#include "JLinkObj.h"
#include "JRealData.h"

char* theJRDivideObj = JRDivideObj().Register();
void JRDivideObj::writeContent(JOutputStream& os) {
  JRAbsObj::writeContent(os);
  putDouble(os, "v0", v[0]);
  putDouble(os, "v1", v[1]);
}

void JRDivideObj::readContent(JDictionary& dict) {
  JRAbsObj::readContent(dict);
  v[0] = getDouble(dict, "v0");
  v[1] = getDouble(dict, "v1");
}

const char* JRDivideObj::className() const { return "JRDivideObj";}
JObject* JRDivideObj::clone() const { return new JRDivideObj(*this);}
JRDivideObj::JRDivideObj() 
{ igm = 2; v[0] = v[1] = 0.0;}

void JRDivideObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*5)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*5, y+my);
  g.fillOval(x+bx+dx*2, y+by, dx, dy);
  g.fillOval(x+bx+dx*2, y+by+dy*2, dx, dy);
}

JString JRDivideObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JRDivideObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  link.access(JRealData(v[n]));
  if (v[1] == 0.0) v[1] = 1.0;
  value = v[0] / v[1];
  if (value != oldv)
    broadcast(0);
}

