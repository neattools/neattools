#include "JDelayObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"

char* theJDelayObj = JDelayObj().Register();
void JDelayObj::writeContent(JOutputStream& os) {
  JAbsObj::writeContent(os);
  putInteger(os, "nvalue", nvalue);
}

void JDelayObj::readContent(JDictionary& dict) {
  JAbsObj::readContent(dict);
  nvalue = getInteger(dict, "nvalue");
}

const char* JDelayObj::className() const { return "JDelayObj";}
JObject* JDelayObj::clone() const { return new JDelayObj(*this);}
JDelayObj::JDelayObj() { nvalue = 0;}

void JDelayObj::draw(JGraphics g, int x, int y, int w, int h) {
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

void JDelayObj::engine(int n, JLinkObj& link) {
  value = nvalue;
  broadcast(0);
  link.access(JIntegerData(nvalue));
}
