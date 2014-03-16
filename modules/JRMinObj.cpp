#include "JRMinObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JDouble.h"
#include "JRealData.h"

char* theJRMinObj = JRMinObj().Register();
const char* JRMinObj::className() const { return "JRMinObj";}
JObject* JRMinObj::clone() const { return new JRMinObj(*this);}

void JRMinObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Min"), rect);
}

void DoRMinEngin(const JObject* obj, void** arg) {
  double iv = 0.0;
  ((JLinkObj*)obj)->access(JRealData(iv));
  *(double*)arg = min(*(double*)arg, iv);
}

void JRMinObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  inputSet(n).forEachChild(DoRMinEngin, 
    (void**)&(value = JDouble::MAX_VALUE));
  if (value != oldv)
    broadcast(n);
}
