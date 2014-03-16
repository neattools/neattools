#include "JCSinhObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JComplexData.h"

char* theJCSinhObj = JCSinhObj().Register();

const char* JCSinhObj::className() const { return "JCSinhObj";}
JObject* JCSinhObj::clone() const { return new JCSinhObj(*this);}

void JCSinhObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CSinh"), rect);
}

void JCSinhObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  jcomplex iv;
  link.access(JComplexData(iv = 0));
  value = JMath::sinh(iv);
  if (value != oldv)
    broadcast(0);
}
