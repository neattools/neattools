#include "JItoRObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JRealData.h"
#include "JMath.h"

char* theJItoRObj = JItoRObj().Register();

void JItoRObj::writeContent(JOutputStream& os) {
  JRAbsObj::writeContent(os);
  putInteger(os, "ival", ival);
}

void JItoRObj::readContent(JDictionary& dict) {
  JRAbsObj::readContent(dict);
  ival = getInteger(dict, "ival");
}

const char* JItoRObj::className() const { return "JItoRObj";}
JObject* JItoRObj::clone() const { return new JItoRObj(*this);}

void JItoRObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = value;}
int JItoRObj::inputType(int n) { return JIntegerData::id;}
void JItoRObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ItoR"), rect);
}

void JItoRObj::engine(int n, JLinkObj& link) {
  link.access(JIntegerData(ival));
  value = (double)ival;
  broadcast(0);
}
