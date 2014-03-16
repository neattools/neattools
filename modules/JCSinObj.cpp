#include "JCSinObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCSinObj = JCSinObj().Register();

const char* JCSinObj::className() const { return "JCSinObj";}
JObject* JCSinObj::clone() const { return new JCSinObj(*this);}

void JCSinObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CSin"), rect);
}

boolean JCSinObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JCSinObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::sin(iv);
  if (value != oldv)
    broadcast(0);
}
