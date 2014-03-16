#include "JRRandomObj.h"
#include "JInteger.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"

char* theJRRandomObj = JRRandomObj().Register();
const char* JRRandomObj::className() const { return "JRRandomObj";}
JObject* JRRandomObj::clone() const { return new JRRandomObj(*this);}

JRRandomObj::JRRandomObj() { ivalue = 0;}
JString JRRandomObj::inputTag(int n) { return "control(logical)";}
int JRRandomObj::inputType(int n) { return JIntegerData::id;}
int JRRandomObj::inputFace(int n) { return TOP;}
JFRect JRRandomObj::inputArea(int n) 
{ return topArea(n, 0, 1);}
JFPoint JRRandomObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, 1);}


void JRRandomObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Rand"), rect);
}

void JRRandomObj::engine(int n, JLinkObj& link) {
  int ovalue = ivalue;
  link.access(JIntegerData(ivalue));
  ivalue = (ivalue != 0);
  if ((ivalue != ovalue) && ivalue) {
    value = JMath::random();
    broadcast(0);
  }
}
