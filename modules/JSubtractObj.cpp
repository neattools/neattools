#include "JSubtractObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJSubtractObj = JSubtractObj().Register();
const char* JSubtractObj::className() const { return "JSubtractObj";}
JObject* JSubtractObj::clone() const { return new JSubtractObj(*this);}

void JSubtractObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
}

void JSubtractObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(v[n]));
  value = (v[0] - v[1]);
  if (value != oldv)
    broadcast(0);
}

