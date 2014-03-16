#include "JDEqualObj.h"
#include "JLinkObj.h"
#include "JDateData.h"

char* theJDEqualObj = JDEqualObj().Register();
const char* JDEqualObj::className() const { return "JDEqualObj";}
JObject* JDEqualObj::clone() const { return new JDEqualObj(*this);}

void JDEqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy)/2;
  g.drawLine(x+bx, y+by, x+bx+dx*3, y+by);
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
}

void JDEqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JDateData(v[n]));
  value = (v[0] == v[1]) ? mask : 0;
  if (value != oldv)
    broadcast(0);
}

