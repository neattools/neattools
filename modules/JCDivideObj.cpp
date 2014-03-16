#include "JCDivideObj.h"
#include "JLinkObj.h"
#include "JComplexData.h"

char* theJCDivideObj = JCDivideObj().Register();
const char* JCDivideObj::className() const { return "JCDivideObj";}
JObject* JCDivideObj::clone() const { return new JCDivideObj(*this);}

void JCDivideObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*5)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*5, y+my);
  g.fillOval(x+bx+dx*2, y+by, dx, dy);
  g.fillOval(x+bx+dx*2, y+by+dy*2, dx, dy);
}

void JCDivideObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JComplexData(v[n]));
  if (v[1] == 0.0) v[1] = 1.0;
  value = v[0] / v[1];
  if (value != oldv)
    broadcast(0);
}

