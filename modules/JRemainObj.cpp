#include "JRemainObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"

char* theJRemainObj = JRemainObj().Register();
const char* JRemainObj::className() const { return "JRemainObj";}
JObject* JRemainObj::clone() const { return new JRemainObj(*this);}

void JRemainObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  g.drawLine(x+bx, y+by+dy*3, x+bx+dx*3, y+by);
  g.drawOval(x+bx, y+by, dx, dy);
  g.drawOval(x+bx+dx*2, y+by+dy*2, dx, dy);
}

void JRemainObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  value = JMath::imod(v[0], v[1]);
  if (value != oldv)
    broadcast(0);
}

