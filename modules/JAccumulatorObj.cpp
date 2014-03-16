#include "JAccumulatorObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJAccumulatorObj = JAccumulatorObj().Register();
const char* JAccumulatorObj::className() const { return "JAccumulatorObj";}
JObject* JAccumulatorObj::clone() const { return new JAccumulatorObj(*this);}

void JAccumulatorObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/4;
  int by = (h-dy*2)/2;
  int xx[] = { x+bx, x+bx+dx, x+bx+dx, 
    x+bx+dx*2, x+bx+dx*2, x+bx+dx*3};
  int yy[] = { y+by+dy*2, y+by+dy*2, y+by+dy, 
    y+by+dy, y+by, y+by};
  g.drawPolygon(xx, yy, 6);
}

JString JAccumulatorObj::inputTag(int n) { 
  char* tag[] = { "clock(logical)", "enable(logical)"};
  return tag[n];
}

void JAccumulatorObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int oldv = v[0];
    link.access(JIntegerData(v[0]));
    v[0] = (v[0] != 0);
    if ((v[0] != oldv) && v[0] && v[1]) {
      value++;
      broadcast(0);
    }
  } else {
    int oldv = v[1];
    link.access(JIntegerData(v[1]));
    v[1] = (v[1] != 0);
    if ((v[1] != oldv) && !v[1]) {
      value = 0;
      broadcast(0);
    }
  }
}

