#include "JBtoSObj.h"
#include "JLinkObj.h"
#include "JStringData.h"
#include "JBlock.h"
#include "JBytesData.h"

char* theJBtoSObj = JBtoSObj().Register();
const char* JBtoSObj::className() const { return "JBtoSObj";}
JObject* JBtoSObj::clone() const { return new JBtoSObj(*this);}
JBtoSObj::JBtoSObj() { moduleColor = JStringData::color;}
int JBtoSObj::inputType(int n) { return JBytesData::id;}
void JBtoSObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("BtoS"), rect);
}

void JBtoSObj::engine(int n, JLinkObj& link) {
  JBlock iv;
  link.access(JBlockData(iv));
  value = JString(iv);
  broadcast(0);
}
