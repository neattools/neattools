#include "JNOTObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"

char* theJNOTObj = JNOTObj().Register();
const char* JNOTObj::className() const { return "JNOTObj";}
JObject* JNOTObj::clone() const { return new JNOTObj(*this);}

boolean JNOTObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JNOTObj::draw(JGraphics g, int x, int y, int w, int h) {
  int xx[] = { x, x+w-6, x, x};
  int yy[] = { y, y+(h-1)/2, y+h-1, y};
  g.drawPolygon(xx, yy, 4);
  g.drawOval(x+w-5, y+(h-1)/2-2, 5, 5);
}

void JNOTObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JIntegerData(value));
  value = (~value & mask);
  if (value != oldv)
    broadcast(0);
}
