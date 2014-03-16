#include "JREqualObj.h"
#include "JLinkObj.h"
#include "JRealData.h"

char* theJREqualObj = JREqualObj().Register();
const char* JREqualObj::className() const { return "JREqualObj";}
JObject* JREqualObj::clone() const { return new JREqualObj(*this);}

void JREqualObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy)/2;
  g.drawLine(x+bx, y+by, x+bx+dx*3, y+by);
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
}

void JREqualObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JRealData(v[n]));
  value = (v[0] == v[1]) ? mask : 0;
  if (value != oldv)
    broadcast(0);
}

