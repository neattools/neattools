#include "JCExpObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCExpObj = JCExpObj().Register();

const char* JCExpObj::className() const { return "JCExpObj";}
JObject* JCExpObj::clone() const { return new JCExpObj(*this);}

void JCExpObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CExp"), rect);
}

void JCExpObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::exp(iv);
  if (value != oldv)
    broadcast(0);
}
