#include "JMultiplyObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"

char* theJMultiplyObj = JMultiplyObj().Register();
const char* JMultiplyObj::className() const { return "JMultiplyObj";}
JObject* JMultiplyObj::clone() const { return new JMultiplyObj(*this);}

void JMultiplyObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  g.drawLine(x+bx, y+by+dy*3, x+bx+dx*3, y+by);
  g.drawLine(x+bx+dx*3, y+by+dy*3, x+bx, y+by);
}

void DoMultiplyEngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg *= iv;
}

void JMultiplyObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoMultiplyEngin, (void**)&(value = 1));
  if (value != oldv)
    broadcast(0);
}
