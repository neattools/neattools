#include "JMinObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JInteger.h"
#include "JIntegerData.h"

char* theJMinObj = JMinObj().Register();
const char* JMinObj::className() const { return "JMinObj";}
JObject* JMinObj::clone() const { return new JMinObj(*this);}

void JMinObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Min"), rect);
}

void DoMinEngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg = min(*(int*)arg, iv);
}

void JMinObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoMinEngin, 
    (void**)&(value = JInteger::MAX_VALUE));
  if (value != oldv) 
    broadcast(0);
}
