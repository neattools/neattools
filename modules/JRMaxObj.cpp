#include "JRMaxObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JDouble.h"
#include "JRealData.h"

char* theJRMaxObj = JRMaxObj().Register();
const char* JRMaxObj::className() const { return "JRMaxObj";}
JObject* JRMaxObj::clone() const { return new JRMaxObj(*this);}

void JRMaxObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Max"), rect);
}

void DoRMaxEngin(const JObject* obj, void** arg) { 
  double iv = 0.0;
  ((JLinkObj*)obj)->access(JRealData(iv));
  *(double*)arg = max(*(double*)arg, iv);
}

void JRMaxObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  inputSet(n).forEachChild(DoRMaxEngin, 
    (void**)&(value = JDouble::MIN_VALUE));
  if (value != oldv)
    broadcast(n);
}
