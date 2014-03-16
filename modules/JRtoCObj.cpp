#include "JRtoCObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"
#include "JComplexData.h"

char* theJRtoCObj = JRtoCObj().Register();

void JRtoCObj::readContent(JDictionary& dict) {
  JCAddObj::readContent(dict);
  iv[0] = value.r;
  iv[1] = value.i;
}

const char* JRtoCObj::className() const { return "JRtoCObj";}
JObject* JRtoCObj::clone() const { return new JRtoCObj(*this);}

JRtoCObj::JRtoCObj() {
  igm = 2;
  iv[0] = iv[1] = 0;
}

void JRtoCObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("RtoC"), rect);
}

int JRtoCObj::inputType(int n) {
  return JRealData::id;
}

JString JRtoCObj::inputTag(int n) { 
  char* tag[] = { "real", "imag"};
  return tag[n];
}

boolean JRtoCObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JRtoCObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JRealData(iv[n]));
  value = jcomplex(iv[0], iv[1]);
  if (value != oldv)
    broadcast(0);
}
