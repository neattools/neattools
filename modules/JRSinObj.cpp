#include "JRSinObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRSinObj = JRSinObj().Register();
const char* JRSinObj::className() const { return "JRSinObj";}
JObject* JRSinObj::clone() const { return new JRSinObj(*this);}

void JRSinObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Sin"), rect);
}

void JRSinObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::sin(value);
  if (value != ovalue)
    broadcast(0);
}
