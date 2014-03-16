#include "JPowObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"

char* theJPowObj = JPowObj().Register();
const char* JPowObj::className() const { return "JPowObj";}
JObject* JPowObj::clone() const { return new JPowObj(*this);}

void JPowObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*2)/2;
  int dy = h/5;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx, x+bx+dx*2};
  int yy[] = { y+by+dy*2, y+by, y+by+dy*2};
  g.drawPolygon(xx, yy, 3);
}

void JPowObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  if (v[1] < 0) v[1] = 0;
  value = JMath::ipow(v[0], v[1]);
  if (value != oldv)
    broadcast(0);
}

