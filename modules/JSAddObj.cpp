#include "JSAddObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSAddObj = JSAddObj().Register();

void JSAddObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putString(os, "value", value);
}

void JSAddObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  value = getString(dict, "value");
}

const char* JSAddObj::className() const { return "JSAddObj";}
JObject* JSAddObj::clone() const { return new JSAddObj(*this);}
JSAddObj::JSAddObj() { 
  igm = 1; 
  moduleColor = JStringData::color;
}

void JSAddObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int mx = w/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
  g.drawLine(x+mx, y+by, x+mx, y+by+dy*4);
}

void JSAddObj::access(int n, JLinkObj& link, const JDataType& data) 
{ JSTRING(data) = value;}
int JSAddObj::inputType(int n) { return JStringData::id;}
int JSAddObj::outputType(int n) { return JStringData::id;}
boolean JSAddObj::inputAllowed(int n) { return true;}
boolean JSAddObj::outputAllowed(int n) { return true;}

void DoSAddEngin(const JObject* obj, void** arg) { 
  JString iv;
  ((JLinkObj*)obj)->access(JStringData(iv));
  *(JString*)arg += iv;
}

void JSAddObj::engine(int n, JLinkObj& link) {
  JString oldv = value;
  inputSet(n).forEachChild(DoSAddEngin, 
    (void**)&(value=""));
  if (value != oldv) 
    broadcast(0);
}
