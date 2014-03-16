#include "JSLowerObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSLowerObj = JSLowerObj().Register();
const char* JSLowerObj::className() const { return "JSLowerObj";}
JObject* JSLowerObj::clone() const { return new JSLowerObj(*this);}
boolean JSLowerObj::inputAllowed(int n) { return !inputSet(n).last();}
void JSLowerObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Lower"), rect);
}

void JSLowerObj::engine(int n, JLinkObj& link) {
  JString iv;
  link.access(JStringData(iv));
  JString ov = value;
  value = iv.toLowerCase();
  if (value != ov) broadcast(0);
}
