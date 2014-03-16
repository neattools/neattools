#include "JRExpObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRExpObj = JRExpObj().Register();
const char* JRExpObj::className() const { return "JRExpObj";}
JObject* JRExpObj::clone() const { return new JRExpObj(*this);}

void JRExpObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Exp"), rect);
}

void JRExpObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::exp(value);
  if (value != ovalue)
    broadcast(0);
}
