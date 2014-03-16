#include "JCAddObj.h"
#include "JLinkObj.h"
#include "JComplexData.h"

char* theJCAddObj = JCAddObj().Register();

void JCAddObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putDouble(os, "real", value.r);
  putDouble(os, "imag", value.i);
}

void JCAddObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  value.r = getDouble(dict, "real");
  value.i = getDouble(dict, "imag");
}

const char* JCAddObj::className() const { return "JCAddObj";}
JObject* JCAddObj::clone() const { return new JCAddObj(*this);}
JCAddObj::JCAddObj() {
  igm = 1; 
  value = 0.0;
  moduleColor = JComplexData::color;
}

void JCAddObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int mx = w/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
  g.drawLine(x+mx, y+by, x+mx, y+by+dy*4);
}

void JCAddObj::access(int n, JLinkObj& link, const JDataType& data) 
{ JCOMPLEX(data) = value;}
int JCAddObj::inputType(int n) { return JComplexData::id;}
int JCAddObj::outputType(int n) { return JComplexData::id;}
boolean JCAddObj::inputAllowed(int n) { return true;}
boolean JCAddObj::outputAllowed(int n) { return true;}

void DoCAddEngin(const JObject* obj, void** arg) { 
  jcomplex iv;
  ((JLinkObj*)obj)->access(JComplexData(iv));
  *(jcomplex*)arg += iv;
}

void JCAddObj::engine(int n, JLinkObj& link) {
  jcomplex oldv = value;
  inputSet(n).forEachChild(DoCAddEngin, 
    (void**)&(value = 0.0));
  if (value != oldv) 
    broadcast(0);
}
