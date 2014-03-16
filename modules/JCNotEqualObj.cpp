#include "JCNotEqualObj.h"
#include "JLinkObj.h"
#include "JComplexData.h"

char* theJCNotEqualObj = JCNotEqualObj().Register();
const char* JCNotEqualObj::className() const { return "JCNotEqualObj";}
JObject* JCNotEqualObj::clone() const { return new JCNotEqualObj(*this);}

void JCNotEqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy)/2;
  g.drawLine(x+bx, y+by, x+bx+dx*3, y+by);
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
  g.drawLine(x+bx+dx, y+by+dy*2, x+bx+dx*2, y+by-dy);
}

void JCNotEqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JComplexData(v[n]));
  value = (v[0] != v[1]) ? mask : 0;
  if (value != oldv)
    broadcast(0);
}

