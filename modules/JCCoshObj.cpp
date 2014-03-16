#include "JCCoshObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCCoshObj = JCCoshObj().Register();

const char* JCCoshObj::className() const { return "JCCoshObj";}
JObject* JCCoshObj::clone() const { return new JCCoshObj(*this);}

void JCCoshObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CCosh"), rect);
}

void JCCoshObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::cosh(iv);
  if (value != oldv)
    broadcast(0);
}
