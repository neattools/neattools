#include "JBtoIObj.h"
#include "JLinkObj.h"
#include "JBytesData.h"

char* theJBtoIObj = JBtoIObj().Register();
const char* JBtoIObj::className() const { return "JBtoIObj";}
JObject* JBtoIObj::clone() const { return new JBtoIObj(*this);}
JBtoIObj::JBtoIObj() { moduleColor = JBytesData::color;}
int JBtoIObj::inputType(int n) { return JBytesData::id;}
JString JBtoIObj::outputTag(int n) { return "output(8bits)";}
void JBtoIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("BtoI"), rect);
}

void JBtoIObj::engine(int n, JLinkObj& link) {
  JBlock data;
  link.access(JBytesData(data));
  int sz = data.size();
  uchar* buf = (uchar*)(char*)data;
  for (int i=0; i<sz; i++) {
    value = (int)buf[i];
    broadcast(0);
  }
}
