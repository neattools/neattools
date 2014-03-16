#include "JRTanObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRTanObj = JRTanObj().Register();
const char* JRTanObj::className() const { return "JRTanObj";}
JObject* JRTanObj::clone() const { return new JRTanObj(*this);}

void JRTanObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Tan"), rect);
}

void JRTanObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::tan(value);
  if (value != ovalue)
    broadcast(0);
}
