#include "JItoSObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBlock.h"
#include "JStringData.h"

char* theJItoSObj = JItoSObj().Register();
const char* JItoSObj::className() const { return "JItoSObj";}
JObject* JItoSObj::clone() const { return new JItoSObj(*this);}
JItoSObj::JItoSObj() { moduleColor = JStringData::color; s[1] = 0;}
int JItoSObj::outputType(int n) { return JStringData::id;}
JString JItoSObj::inputTag(int n) { return "input(8bits)";}
void JItoSObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ItoS"), rect);
}

void JItoSObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(JString(s, JString::needCopy));}

void JItoSObj::engine(int n, JLinkObj& link) {
  int iv;
  link.access(JIntegerData(iv));
  s[0] = (uchar)iv;
  broadcast(0);
}
