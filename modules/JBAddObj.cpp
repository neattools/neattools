#include "JBAddObj.h"
#include "JLinkObj.h"
#include "JBytesData.h"

char* theJBAddObj = JBAddObj().Register();

void JBAddObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putObject(os, "value", value);
}

void JBAddObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  JObject *obj = getObject(dict, "value");
  if (obj) value = *(JBlock*)obj;
}

const char* JBAddObj::className() const { return "JBAddObj";}
JObject* JBAddObj::clone() const { return new JBAddObj(*this);}
JBAddObj::JBAddObj() { 
  igm = 1; 
  moduleColor = JBytesData::color;
}

void JBAddObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int mx = w/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
  g.drawLine(x+mx, y+by, x+mx, y+by+dy*4);
}

void JBAddObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(value);}
int JBAddObj::inputType(int n) { return JBytesData::id;}
int JBAddObj::outputType(int n) { return JBytesData::id;}
boolean JBAddObj::inputAllowed(int n) { return true;}
boolean JBAddObj::outputAllowed(int n) { return true;}

void DoBAddEngin(const JObject* obj, void** arg) { 
  JBlock iv;
  ((JLinkObj*)obj)->access(JBlockData(iv));
  *(JBlock*)arg += iv;
}

void JBAddObj::engine(int n, JLinkObj& link) {
  JString oldv = value;
  inputSet(n).forEachChild(DoBAddEngin, 
    (void**)&(value=JBlock()));
  if (value != oldv) 
    broadcast(0);
}
