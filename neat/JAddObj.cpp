#include "JAddObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JMath.h"

#if defined(_NEAT_DLL)
  DllExport
#endif
char* theJAddObj = JAddObj().Register();
void JAddObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putInteger(os, "value", value);
}

void JAddObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  value = getInteger(dict, "value");
}

const char* JAddObj::className() const { return "JAddObj";}
JObject* JAddObj::clone() const { return new JAddObj(*this);}
JAddObj::JAddObj() { igm = 1; value = 0;}

void JAddObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/7;
  int bx = (w-dx*4)/2;
  int dy = h/7;
  int by = (h-dy*4)/2;
  int mx = w/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx*4, y+my);
  g.drawLine(x+mx, y+by, x+mx, y+by+dy*4);
}

void JAddObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = value;}
boolean JAddObj::inputAllowed(int n) { return true;}
boolean JAddObj::outputAllowed(int n) { return true;}

void DoAddEngin(const JObject* obj, void** arg) { 
  int iv = 0;
  ((JLinkObj*)obj)->access(JIntegerData(iv));
  *(int*)arg += iv;
}

void JAddObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  inputSet(n).forEachChild(DoAddEngin, (void**)&(value = 0));
  if (value != oldv) broadcast(0);
}
