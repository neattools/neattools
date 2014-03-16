#include "JRMultiplyObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRMultiplyObj = JRMultiplyObj().Register();
const char* JRMultiplyObj::className() const { return "JRMultiplyObj";}
JObject* JRMultiplyObj::clone() const { return new JRMultiplyObj(*this);}

void JRMultiplyObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  g.drawLine(x+bx, y+by+dy*3, x+bx+dx*3, y+by);
  g.drawLine(x+bx+dx*3, y+by+dy*3, x+bx, y+by);
}

void DoRMultiplyEngin(const JObject* obj, void** arg) { 
  double iv = 0.0;
  ((JLinkObj*)obj)->access(JRealData(iv));
  *(double*)arg *= iv;
}

void JRMultiplyObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  inputSet(n).forEachChild(DoRMultiplyEngin, (void**)&(value = 1));
  if (value != oldv)
    broadcast(0);
}
