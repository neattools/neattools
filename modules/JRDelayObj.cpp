#include "JRDelayObj.h"
#include "JRealData.h"
#include "JLinkObj.h"

char* theJRDelayObj = JRDelayObj().Register();
void JRDelayObj::writeContent(JOutputStream& os) {
  JRAbsObj::writeContent(os);
  putDouble(os, "nvalue", nvalue);
}

void JRDelayObj::readContent(JDictionary& dict) {
  JRAbsObj::readContent(dict);
  nvalue = getDouble(dict, "nvalue");
}

const char* JRDelayObj::className() const { return "JRDelayObj";}
JObject* JRDelayObj::clone() const { return new JRDelayObj(*this);}
JRDelayObj::JRDelayObj() { nvalue = 0;}

void JRDelayObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/9;
  int bx = (w-dx*7)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int x1[] = { x+bx+dx, x+bx+dx*3, x+bx+dx*3, 
    x+bx+dx*5, x+bx+dx*5, x+bx+dx*7};
  int y1[] = { y+by+dy*3, y+by+dy*3, y+by, 
    y+by, y+by+dy*3, y+by+dy*3};
  g.drawPolygon(x1, y1, 6);
  int x2[] = { x+bx, x+bx+dx*2, x+bx+dx*2, 
    x+bx+dx*4, x+bx+dx*4, x+bx+dx*6};
  int y2[] = { y+by+dy*4, y+by+dy*4, y+by+dy, 
    y+by+dy, y+by+dy*4, y+by+dy*4};
  g.drawPolygon(x2, y2, 6);
}

void JRDelayObj::engine(int n, JLinkObj& link) {
  value = nvalue;
  broadcast(0);
  link.access(JRealData(nvalue));
}
