#include "JRATanObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRATanObj = JRATanObj().Register();
const char* JRATanObj::className() const { return "JRATanObj";}
JObject* JRATanObj::clone() const { return new JRATanObj(*this);}

void JRATanObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ATan"), rect);
}

void JRATanObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::atan(value);
  if (value != ovalue)
    broadcast(0);
}
