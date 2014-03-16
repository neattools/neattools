#include "JPolrCObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"
#include "JComplexData.h"

char* theJPolrCObj = JPolrCObj().Register();

void JPolrCObj::readContent(JDictionary& dict) {
  JRtoCObj::readContent(dict);
  iv[0] = value.abs();
  iv[1] = value.arg();
}

const char* JPolrCObj::className() const { return "JPolrCObj";}
JObject* JPolrCObj::clone() const { return new JPolrCObj(*this);}

void JPolrCObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("PolrC"), rect);
}

JString JPolrCObj::inputTag(int n) { 
  char* tag[] = { "R", "Theta"};
  return tag[n];
}

void JPolrCObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JRealData(iv[n]));
  value = JMath::polar(iv[0], iv[1]);
  if (value != oldv)
    broadcast(0);
}
