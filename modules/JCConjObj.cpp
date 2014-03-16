#include "JCConjObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCConjObj = JCConjObj().Register();

const char* JCConjObj::className() const { return "JCConjObj";}
JObject* JCConjObj::clone() const { return new JCConjObj(*this);}

void JCConjObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CConj"), rect);
}

void JCConjObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::conjg(iv);
  if (value != oldv)
    broadcast(0);
}
