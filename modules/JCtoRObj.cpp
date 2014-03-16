#include "JCtoRObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"
#include "JComplexData.h"

char* theJCtoRObj = JCtoRObj().Register();

void JCtoRObj::readContent(JDictionary& dict) {
  JCAddObj::readContent(dict);
  v[0] = value.r;
  v[1] = value.i;
}

const char* JCtoRObj::className() const { return "JCtoRObj";}
JObject* JCtoRObj::clone() const { return new JCtoRObj(*this);}

JCtoRObj::JCtoRObj() {
  ogm = 2;
  v[0] = v[1] = 0;
}

void JCtoRObj::access(int n, JLinkObj& link, const JDataType& data) { 
  DOUBLE(data) = v[n];
}

void JCtoRObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("CtoR"), rect);
}

boolean JCtoRObj::inputAllowed(int n)
{ return !inputSet(n).last();}

int JCtoRObj::outputType(int n) {
  return JRealData::id;
}

JString JCtoRObj::outputTag(int n) { 
  char* tag[] = { "real", "imag"};
  return tag[n];
}

int JCtoRObj::outputFace(int n) {
  return (n) ? BOTTOM : RIGHT;
}

JFRect JCtoRObj::outputArea(int n) {
  return (n) ? bottomArea(n, 1, 1) : rightArea(n, 0, 1);
}

JFPoint JCtoRObj::outputPoint(int n, JLinkObj& link) {
  return (n) ? bottomPoint(n, link, 1, 1) : rightPoint(n, link, 0, 1);
}

void JCtoRObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JComplexData(value));
  if (value != oldv) {
    v[0] = value.r;
    v[1] = value.i;
    broadcast(0);
    broadcast(1);
  }
}
