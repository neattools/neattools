#include "JDivideObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJDivideObj = JDivideObj().Register();
void JDivideObj::writeContent(JOutputStream& os) {
  JAbsObj::writeContent(os);
  putInteger(os, "v0", v[0]);
  putInteger(os, "v1", v[1]);
}

void JDivideObj::readContent(JDictionary& dict) {
  JAbsObj::readContent(dict);
  v[0] = getInteger(dict, "v0");
  v[1] = getInteger(dict, "v1");
}

const char* JDivideObj::className() const { return "JDivideObj";}
JObject* JDivideObj::clone() const { return new JDivideObj(*this);}
JDivideObj::JDivideObj() 
{ igm = 2; v[0] = v[1] = 0;}

void JDivideObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*5)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*5, y+my);
  g.fillOval(x+bx+dx*2, y+by, dx, dy);
  g.fillOval(x+bx+dx*2, y+by+dy*2, dx, dy);
}

JString JDivideObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

boolean JDivideObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JDivideObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  if (v[1] == 0) v[1] = 1;
  value = v[0] / v[1];
  if (value != oldv)
    broadcast(0);
}

