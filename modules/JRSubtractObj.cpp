#include "JRSubtractObj.h"
#include "JLinkObj.h"
#include "JRealData.h"

char* theJRSubtractObj = JRSubtractObj().Register();
const char* JRSubtractObj::className() const { return "JRSubtractObj";}
JObject* JRSubtractObj::clone() const { return new JRSubtractObj(*this);}

void JRSubtractObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
}

void JRSubtractObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  link.access(JRealData(v[n]));
  value = (v[0] - v[1]);
  if (value != oldv)
    broadcast(0);
}

