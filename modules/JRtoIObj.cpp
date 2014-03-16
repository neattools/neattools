#include "JRtoIObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JIntegerData.h"
#include "JRealData.h"

char* theJRtoIObj = JRtoIObj().Register();

void JRtoIObj::writeContent(JOutputStream& os) {
  JRAbsObj::writeContent(os);
  putInteger(os, "ival", ival);
}

void JRtoIObj::readContent(JDictionary& dict) {
  JRAbsObj::readContent(dict);
  ival = getInteger(dict, "ival");
}

const char* JRtoIObj::className() const { return "JRtoIObj";}
JObject* JRtoIObj::clone() const { return new JRtoIObj(*this);}

void JRtoIObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = ival;}
int JRtoIObj::outputType(int n) { return JIntegerData::id;}
void JRtoIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("RtoI"), rect);
}

void JRtoIObj::engine(int n, JLinkObj& link) {
  link.access(JRealData(value));
  ival = JMath::round(value);
  broadcast(0);
}
