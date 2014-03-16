#include "JRPowObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JArithmeticException.h"
#include "JRealData.h"

char* theJRPowObj = JRPowObj().Register();
const char* JRPowObj::className() const { return "JRPowObj";}
JObject* JRPowObj::clone() const { return new JRPowObj(*this);}

void JRPowObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*2)/2;
  int dy = h/5;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx, x+bx+dx*2};
  int yy[] = { y+by+dy*2, y+by, y+by+dy*2};
  g.drawPolygon(xx, yy, 3);
}

void JRPowObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  link.access(JRealData(v[n]));
  if (v[1] < 0) v[1] = 0;
  try {
    value = JMath::pow(v[0], v[1]);
  } catch (JArithmeticException* e) {
    delete e;
    value = 0.0;
  }
  if (value != oldv)
    broadcast(0);
}

