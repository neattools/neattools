#include "JRASinObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRASinObj = JRASinObj().Register();
const char* JRASinObj::className() const { return "JRASinObj";}
JObject* JRASinObj::clone() const { return new JRASinObj(*this);}

void JRASinObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ASin"), rect);
}

void JRASinObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = JMath::asin(max(-1.0, min(1.0, value)));
  if (value != ovalue)
    broadcast(0);
}
