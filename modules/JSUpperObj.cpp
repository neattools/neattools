#include "JSUpperObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSUpperObj = JSUpperObj().Register();
const char* JSUpperObj::className() const { return "JSUpperObj";}
JObject* JSUpperObj::clone() const { return new JSUpperObj(*this);}
boolean JSUpperObj::inputAllowed(int n) { return !inputSet(n).last();}
void JSUpperObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Upper"), rect);
}

void JSUpperObj::engine(int n, JLinkObj& link) {
  JString iv;
  link.access(JStringData(iv));
  JString ov = value;
  value = iv.toUpperCase();
  if (value != ov) broadcast(0);
}
