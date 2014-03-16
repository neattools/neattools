#include "JRtoDObj.h"
#include "JLinkObj.h"
#include "JMath.h"
#include "JDateData.h"
#include "JRealData.h"

char* theJRtoDObj = JRtoDObj().Register();

void JRtoDObj::writeContent(JOutputStream& os) {
  JRAbsObj::writeContent(os);
  putDouble(os, "rval", (double)date);
}

void JRtoDObj::readContent(JDictionary& dict) {
  JRAbsObj::readContent(dict);
  date = JDate(getDouble(dict, "rval"));
}

const char* JRtoDObj::className() const { return "JRtoDObj";}
JObject* JRtoDObj::clone() const { return new JRtoDObj(*this);}

void JRtoDObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(date);}
int JRtoDObj::outputType(int n) { return JDateData::id;}
void JRtoDObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("RtoD"), rect);
}

void JRtoDObj::engine(int n, JLinkObj& link) {
  link.access(JRealData(value));
  date = JDate(value);
  broadcast(0);
}
