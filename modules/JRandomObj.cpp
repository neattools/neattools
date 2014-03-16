#include "JRandomObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"
#include "JMath.h"

char* theJRandomObj = JRandomObj().Register();
const char* JRandomObj::className() const { return "JRandomObj";}
JObject* JRandomObj::clone() const { return new JRandomObj(*this);}

JRandomObj::JRandomObj() { ivalue = 0;}
JString JRandomObj::inputTag(int n) { return "control(logical)";}
int JRandomObj::inputFace(int n) { return TOP;}
JFRect JRandomObj::inputArea(int n) 
{ return topArea(n, 0, 1);}
JFPoint JRandomObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, 1);}


void JRandomObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Rand"), rect);
}

void JRandomObj::engine(int n, JLinkObj& link) {
  int ovalue = ivalue;
  link.access(JIntegerData(ivalue));
  ivalue = (ivalue != 0);
  if ((ivalue != ovalue) && ivalue) {
    value = JMath::rand() & mask;
    broadcast(0);
  }
}
