#include "JSLenObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSLenObj = JSLenObj().Register();
const char* JSLenObj::className() const { return "JSLenObj";}
JObject* JSLenObj::clone() const { return new JSLenObj(*this);}
void JSLenObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Len"), rect);
}

void JSLenObj::engine(int n, JLinkObj& link) {
  JString data;
  link.access(JStringData(data));
  int ov = value;
  value = data.length();
  if (value != ov) broadcast(0);
}
