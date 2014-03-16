#include "JCCosObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCCosObj = JCCosObj().Register();

const char* JCCosObj::className() const { return "JCCosObj";}
JObject* JCCosObj::clone() const { return new JCCosObj(*this);}

void JCCosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CCos"), rect);
}

void JCCosObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::cos(iv);
  if (value != oldv)
    broadcast(0);
}
