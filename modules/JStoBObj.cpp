#include "JStoBObj.h"
#include "JLinkObj.h"
#include "JStringData.h"
#include "JBlock.h"
#include "JBytesData.h"

char* theJStoBObj = JStoBObj().Register();
const char* JStoBObj::className() const { return "JStoBObj";}
JObject* JStoBObj::clone() const { return new JStoBObj(*this);}
JStoBObj::JStoBObj() { moduleColor = JStringData::color;}
int JStoBObj::inputType(int n) { return JStringData::id;}
void JStoBObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("StoB"), rect);
}

void JStoBObj::engine(int n, JLinkObj& link) {
  JString iv;
  link.access(JStringData(iv));
  value = JBlock(iv.length(), (char*)iv, JBlock::needCopy);
  broadcast(0);
}
