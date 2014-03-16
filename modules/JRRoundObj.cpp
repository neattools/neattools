#include "JRRoundObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRRoundObj = JRRoundObj().Register();
const char* JRRoundObj::className() const { return "JRRoundObj";}
JObject* JRRoundObj::clone() const { return new JRRoundObj(*this);}

void JRRoundObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Rond"), rect);
}

void JRRoundObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::floor(value+0.5);
  if (value != ovalue)
    broadcast(0);
}
