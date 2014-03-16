#include "JBLenObj.h"
#include "JLinkObj.h"
#include "JBytesData.h"

char* theJBLenObj = JBLenObj().Register();
const char* JBLenObj::className() const { return "JBLenObj";}
JObject* JBLenObj::clone() const { return new JBLenObj(*this);}
void JBLenObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Len"), rect);
}

void JBLenObj::engine(int n, JLinkObj& link) {
  JBlock data;
  link.access(JBytesData(data));
  int ov = value;
  value = data.size();
  if (value != ov) broadcast(0);
}
