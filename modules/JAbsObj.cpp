#include "JAbsObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"
#include "JMath.h"

char* theJAbsObj = JAbsObj().Register();
const char* JAbsObj::className() const { return "JAbsObj";}
JObject* JAbsObj::clone() const { return new JAbsObj(*this);}

boolean JAbsObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JAbsObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Abs"), rect);
}

void JAbsObj::engine(int n, JLinkObj& link) {
  int ovalue = value;
  link.access(JIntegerData(value));
  value = JMath::iabs(value);
  if (value != ovalue)
    broadcast(0);
}
