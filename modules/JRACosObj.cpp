#include "JRACosObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRACosObj = JRACosObj().Register();
const char* JRACosObj::className() const { return "JRACosObj";}
JObject* JRACosObj::clone() const { return new JRACosObj(*this);}

void JRACosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ACos"), rect);
}

void JRACosObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::acos(max(-1.0, min(1.0, value)));
  if (value != ovalue)
    broadcast(0);
}
