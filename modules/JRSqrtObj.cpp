#include "JRSqrtObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JArithmeticException.h"
#include "JRealData.h"

char* theJRSqrtObj = JRSqrtObj().Register();
const char* JRSqrtObj::className() const { return "JRSqrtObj";}
JObject* JRSqrtObj::clone() const { return new JRSqrtObj(*this);}

void JRSqrtObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Sqrt"), rect);
}

void JRSqrtObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  try {
    value = JMath::sqrt(value);
  } catch (JArithmeticException* e) {
    delete e;
    value = 0.0;
  }
  if (value != ovalue)
    broadcast(0);
}
