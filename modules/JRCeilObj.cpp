#include "JRCeilObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRCeilObj = JRCeilObj().Register();
const char* JRCeilObj::className() const { return "JRCeilObj";}
JObject* JRCeilObj::clone() const { return new JRCeilObj(*this);}

void JRCeilObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Ceil"), rect);
}

void JRCeilObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::ceil(value);
  if (value != ovalue)
    broadcast(0);
}
