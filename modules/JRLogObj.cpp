#include "JRLogObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JArithmeticException.h"
#include "JRealData.h"

char* theJRLogObj = JRLogObj().Register();
const char* JRLogObj::className() const { return "JRLogObj";}
JObject* JRLogObj::clone() const { return new JRLogObj(*this);}

void JRLogObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Log"), rect);
}

void JRLogObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  try {
    value = JMath::log(value);
  } catch (JArithmeticException* e) {
    delete e;
    value = 0.0;
  }
  if (value != ovalue)
    broadcast(0);
}
