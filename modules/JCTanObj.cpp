#include "JCTanObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCTanObj = JCTanObj().Register();

const char* JCTanObj::className() const { return "JCTanObj";}
JObject* JCTanObj::clone() const { return new JCTanObj(*this);}

void JCTanObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CTan"), rect);
}

void JCTanObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::tan(iv);
  if (value != oldv)
    broadcast(0);
}
