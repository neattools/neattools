#include "JCSubtractObj.h"
#include "JLinkObj.h"
#include "JComplexData.h"

char* theJCSubtractObj = JCSubtractObj().Register();
void JCSubtractObj::writeContent(JOutputStream& os) {
  JCAddObj::writeContent(os);
  putDouble(os, "v0r", v[0].r);
  putDouble(os, "v0i", v[0].i);
  putDouble(os, "v1r", v[1].r);
  putDouble(os, "v1i", v[1].i);
}

void JCSubtractObj::readContent(JDictionary& dict) {
  JCAddObj::readContent(dict);
  v[0].r = getDouble(dict, "v0r");
  v[0].i = getDouble(dict, "v0i");
  v[1].r = getDouble(dict, "v1r");
  v[1].i = getDouble(dict, "v1i");
}

const char* JCSubtractObj::className() const { return "JCSubtractObj";}
JObject* JCSubtractObj::clone() const { return new JCSubtractObj(*this);}

JCSubtractObj::JCSubtractObj() {
  igm = 2; 
}

void JCSubtractObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
}

boolean JCSubtractObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JCSubtractObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JCSubtractObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  link.access(JComplexData(v[n]));
  value = v[0]-v[1];
  if (value != oldv)
    broadcast(0);
}
