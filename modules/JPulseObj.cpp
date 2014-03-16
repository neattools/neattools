#include "JPulseObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"

char* theJPulseObj = JPulseObj().Register();
void JPulseObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "nvalue", nvalue);
}

void JPulseObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  nvalue = getInteger(dict, "nvalue");
}

const char* JPulseObj::className() const { return "JPulseObj";}
JObject* JPulseObj::clone() const { return new JPulseObj(*this);}
JPulseObj::JPulseObj() { nvalue = 0;}
JString JPulseObj::inputTag(int n) { return "input(logical)";}

void JPulseObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/3;
  int by = (h-dy)/2;
  int xx[] = { x+bx, x+bx+dx, x+bx+dx, 
    x+bx+dx*2, x+bx+dx*2, x+bx+dx*3};
  int yy[] = { y+by+dy, y+by+dy, y+by, 
    y+by, y+by+dy, y+by+dy};
  g.drawPolygon(xx, yy, 6);
}

void JPulseObj::engine(int n, JLinkObj& link) {
  int ovalue = nvalue;
  link.access(JIntegerData(nvalue));
  nvalue = (nvalue != 0);
  if ((ovalue != nvalue) && nvalue) {
    value = mask;
    broadcast(0);
    value = 0;
    broadcast(0);
  }
}
