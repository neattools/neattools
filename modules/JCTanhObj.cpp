#include "JCTanhObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCTanhObj = JCTanhObj().Register();

const char* JCTanhObj::className() const { return "JCTanhObj";}
JObject* JCTanhObj::clone() const { return new JCTanhObj(*this);}

void JCTanhObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CTanh"), rect);
}

void JCTanhObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::tanh(iv);
  if (value != oldv)
    broadcast(0);
}
