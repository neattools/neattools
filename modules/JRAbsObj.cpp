#include "JRAbsObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRAbsObj = JRAbsObj().Register();
const char* JRAbsObj::className() const { return "JRAbsObj";}
JObject* JRAbsObj::clone() const { return new JRAbsObj(*this);}

boolean JRAbsObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JRAbsObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Abs"), rect);
}

void JRAbsObj::engine(int n, JLinkObj& link) {
  double ovalue = value;
  link.access(JRealData(value));
  value = jabs(value);
  if (value != ovalue)
    broadcast(0);
}
