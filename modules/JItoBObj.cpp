#include "JItoBObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBlock.h"
#include "JBytesData.h"

char* theJItoBObj = JItoBObj().Register();
const char* JItoBObj::className() const { return "JItoBObj";}
JObject* JItoBObj::clone() const { return new JItoBObj(*this);}
JItoBObj::JItoBObj() { moduleColor = JBytesData::color;}
int JItoBObj::outputType(int n) { return JBytesData::id;}
JString JItoBObj::inputTag(int n) { return "input(8bits)";}
void JItoBObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ItoB"), rect);
}

void JItoBObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(JBlock(1, (char*)&b, JBlock::needCopy));}

void JItoBObj::engine(int n, JLinkObj& link) {
  int iv;
  link.access(JIntegerData(iv));
  b = (uchar)iv;
  broadcast(0);
}
