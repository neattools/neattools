#include "JMaxObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JInteger.h"
#include "JIntegerData.h"

char* theJMaxObj = JMaxObj().Register();
const char* JMaxObj::className() const { return "JMaxObj";}
JObject* JMaxObj::clone() const { return new JMaxObj(*this);}

void JMaxObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Max"), rect);
}

void DoMaxEngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg = max(*(int*)arg, iv);
}

void JMaxObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoMaxEngin, 
    (void**)&(value = JInteger::MIN_VALUE));
  if (value != oldv)
    broadcast(n);
}
