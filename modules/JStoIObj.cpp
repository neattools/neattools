#include "JStoIObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJStoIObj = JStoIObj().Register();
const char* JStoIObj::className() const { return "JStoIObj";}
JObject* JStoIObj::clone() const { return new JStoIObj(*this);}
int JStoIObj::inputType(int n) { return JStringData::id;}
JStoIObj::JStoIObj() { moduleColor = JStringData::color;}
JString JStoIObj::outputTag(int n) { return "output(8bits)";}
void JStoIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("StoI"), rect);
}

void JStoIObj::engine(int n, JLinkObj& link) {
  JString data;
  link.access(JStringData(data));
  uchar* buf = (uchar*)(char*)data;
  while (*buf) {
    value = (int)*buf++;
    broadcast(0);
  }
}
