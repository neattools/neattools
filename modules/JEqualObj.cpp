#include "JEqualObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJEqualObj = JEqualObj().Register();
const char* JEqualObj::className() const { return "JEqualObj";}
JObject* JEqualObj::clone() const { return new JEqualObj(*this);}

void JEqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy)/2;
  g.drawLine(x+bx, y+by, x+bx+dx*3, y+by);
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
}

void JEqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  value = (v[0] == v[1]) ? mask : 0;
  if (value != oldv)
    broadcast(0);
}

