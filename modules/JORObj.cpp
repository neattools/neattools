#include "JORObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JMath.h"

char* theJORObj = JORObj().Register();
const char* JORObj::className() const { return "JORObj";}
JObject* JORObj::clone() const { return new JORObj(*this);}

void JORObj::draw(JGraphics g, int x, int y, int w, int h) {
  int y2 = y+h-1;
  int delta = JMath::round((1.0-JMath::cos(JMath::pi/6))*w);
  g.drawLine(x, y, x+delta, y);
  g.drawLine(x, y2, x+delta, y2);
  g.drawArc(x-w-w+delta, y-(h-1)/2, w+w, h+h, -(30 << 6), 60 << 6);
  g.drawArc(x-w+delta, y-h, w+w, h+h, -(90 << 6), 60 << 6);
  g.drawArc(x-w+delta, y, w+w, h+h, 30 << 6, 60 << 6);
}

void DoOREngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg |= iv;
}

void JORObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoOREngin, 
    (void**)&(value = 0));
  value &= mask;
  if (value != oldv) 
    broadcast(0);
}
