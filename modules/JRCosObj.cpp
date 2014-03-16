#include "JRCosObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRCosObj = JRCosObj().Register();
const char* JRCosObj::className() const { return "JRCosObj";}
JObject* JRCosObj::clone() const { return new JRCosObj(*this);}

void JRCosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Cos"), rect);
}

void JRCosObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::cos(value);
  if (value != ovalue)
    broadcast(0);
}
