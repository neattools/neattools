#include "JXORObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JMath.h"

char* theJXORObj = JXORObj().Register();
const char* JXORObj::className() const { return "JXORObj";}
JObject* JXORObj::clone() const { return new JXORObj(*this);}

void JXORObj::draw(JGraphics g, int x, int y, int w, int h) {
  int y2 = y+h-1;
  int delta = JMath::round((1.0-JMath::cos(JMath::pi/6))*w);
  g.drawLine(x+4, y, x+delta, y);
  g.drawLine(x+4, y2, x+delta, y2);
  g.drawArc(x-w-w+delta+4, y-(h-1)/2, w+w, h+h, -(30 << 6), 60 << 6);
  g.drawArc(x-w-w+delta, y-(h-1)/2, w+w, h+h, -(30 << 6), 60 << 6);
  g.drawArc(x-w+delta, y-h, w+w, h+h, -(90 << 6), 60 << 6);
  g.drawArc(x-w+delta, y, w+w, h+h, 30 << 6, 60 << 6);
}

void DoXOREngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg ^= iv;
}

void JXORObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoXOREngin, 
    (void**)&(value = 0));
  value &= mask;
  if (value != oldv)
    broadcast(0);
}
