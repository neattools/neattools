#include "JRFloorObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRFloorObj = JRFloorObj().Register();
const char* JRFloorObj::className() const { return "JRFloorObj";}
JObject* JRFloorObj::clone() const { return new JRFloorObj(*this);}

void JRFloorObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Flor"), rect);
}

void JRFloorObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::floor(value);
  if (value != ovalue)
    broadcast(0);
}
