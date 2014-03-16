#include "JGreaterEqualObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJGreaterEqualObj = JGreaterEqualObj().Register();
const char* JGreaterEqualObj::className() const { return "JGreaterEqualObj";}
JObject* JGreaterEqualObj::clone() const { return new JGreaterEqualObj(*this);}

void JGreaterEqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx*3, x+bx};
  int yy[] = { y+by+dy*2-2, y+by+dy-2, y+by-2};
  g.drawPolygon(xx, yy, 3);
  g.drawLine(x+bx, y+by+dy*2+2, x+bx+dx*3, y+by+dy+2);
}

void JGreaterEqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  value = (v[0] >= v[1]) ? mask : 0;
  if (value != oldv) 
    broadcast(0);
}

