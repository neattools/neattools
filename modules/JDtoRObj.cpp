#include "JDtoRObj.h"
#include "JLinkObj.h"
#include "JDateData.h"
#include "JRealData.h"
#include "JMath.h"

char* theJDtoRObj = JDtoRObj().Register();
const char* JDtoRObj::className() const { return "JDtoRObj";}
JObject* JDtoRObj::clone() const { return new JDtoRObj(*this);}

void JDtoRObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = value;}
int JDtoRObj::inputType(int n) { return JDateData::id;}
void JDtoRObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("DtoR"), rect);
}

void JDtoRObj::engine(int n, JLinkObj& link) {
  JDate date;
  link.access(JDateData(date));
  value = (double)date;
  broadcast(0);
}
