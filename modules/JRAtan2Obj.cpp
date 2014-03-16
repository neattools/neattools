#include "JRAtan2Obj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRAtan2Obj = JRAtan2Obj().Register();
const char* JRAtan2Obj::className() const { return "JRAtan2Obj";}
JObject* JRAtan2Obj::clone() const { return new JRAtan2Obj(*this);}

void JRAtan2Obj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Atn2"), rect);
}

void JRAtan2Obj::engine(int n, JLinkObj& link) {
  double oldv = value;
  link.access(JRealData(v[n]));
  value = JMath::atan2(v[0], v[1]);
  if (value != oldv)
    broadcast(0);
}

