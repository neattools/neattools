#include "JREObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJREObj = JREObj().Register();
const char* JREObj::className() const { return "JREObj";}
JObject* JREObj::clone() const { return new JREObj(*this);}

void JREObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = JMath::e;}

void JREObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("e"), rect);
}

