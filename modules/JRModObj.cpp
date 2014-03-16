#include "JRModObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRModObj = JRModObj().Register();
const char* JRModObj::className() const { return "JRModObj";}
JObject* JRModObj::clone() const { return new JRModObj(*this);}

void JRModObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Mod"), rect);
}

void JRModObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  link.access(JRealData(v[n]));
  if (v[1] != 0.0)
    value = JMath::mod(v[0], v[1]);
  else value = 0.0;
  if (value != oldv)
    broadcast(0);
}

