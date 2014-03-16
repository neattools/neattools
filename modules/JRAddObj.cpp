#include "JRAddObj.h"
#include "JLinkObj.h"
#include "JRealData.h"

char* theJRAddObj = JRAddObj().Register();

void JRAddObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putDouble(os, "value", value);
}

void JRAddObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  value = getDouble(dict, "value");
}

const char* JRAddObj::className() const { return "JRAddObj";}
JObject* JRAddObj::clone() const { return new JRAddObj(*this);}
JRAddObj::JRAddObj() { 
  igm = 1; 
  value = 0.0;
  moduleColor = JRealData::color;
}

void JRAddObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int mx = w/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
  g.drawLine(x+mx, y+by, x+mx, y+by+dy*4);
}

void JRAddObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = value;}
int JRAddObj::inputType(int n) { return JRealData::id;}
int JRAddObj::outputType(int n) { return JRealData::id;}
boolean JRAddObj::inputAllowed(int n) { return true;}
boolean JRAddObj::outputAllowed(int n) { return true;}

void DoRAddEngin(const JObject* obj, void** arg) { 
  double iv = 0.0;
  ((JLinkObj*)obj)->access(JRealData(iv));
  *(double*)arg += iv;
}

void JRAddObj::engine(int n, JLinkObj& link) {
  double oldv = value;
  inputSet(n).forEachChild(DoRAddEngin, 
    (void**)&(value = 0.0));
  if (value != oldv) 
    broadcast(0);
}
