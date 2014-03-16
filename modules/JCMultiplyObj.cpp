#include "JCMultiplyObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCMultiplyObj = JCMultiplyObj().Register();
const char* JCMultiplyObj::className() const { return "JCMultiplyObj";}
JObject* JCMultiplyObj::clone() const { return new JCMultiplyObj(*this);}

void JCMultiplyObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*3)/2;
  int dy = h/7;
  int by = (h-dy*3)/2;
  g.drawLine(x+bx, y+by+dy*3, x+bx+dx*3, y+by);
  g.drawLine(x+bx+dx*3, y+by+dy*3, x+bx, y+by);
}

void DoCMultiplyEngin(const JObject* obj, void** arg) { 
  jcomplex iv = 0.0;
  ((JLinkObj*)obj)->access(JComplexData(iv));
  *(jcomplex*)arg *= iv;
}

void JCMultiplyObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  inputSet(n).forEachChild(DoCMultiplyEngin, (void**)&(value = 1));
  if (value != oldv)
    broadcast(0);
}
