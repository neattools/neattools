#include "JRPIObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JRealData.h"

char* theJRPIObj = JRPIObj().Register();
const char* JRPIObj::className() const { return "JRPIObj";}
JObject* JRPIObj::clone() const { return new JRPIObj(*this);}
JRPIObj::JRPIObj() { igm=0;}
void JRPIObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = JMath::pi;}
boolean JRPIObj::inputAllowed(int n)
{ return false;}

void JRPIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("PI"), rect);
}

