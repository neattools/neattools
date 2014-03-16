#include "JSPosObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSPosObj = JSPosObj().Register();
void JSPosObj::writeContent(JOutputStream& os) {
  JAbsObj::writeContent(os);
  putString(os, "v0", v[0]);
  putString(os, "v1", v[1]);
}

void JSPosObj::readContent(JDictionary& dict) {
  JAbsObj::readContent(dict);
  v[0] = getString(dict, "v0");
  v[1] = getString(dict, "v1");
}

const char* JSPosObj::className() const { return "JSPosObj";}
JObject* JSPosObj::clone() const { return new JSPosObj(*this);}
JSPosObj::JSPosObj() { 
  igm = 2;;
  moduleColor = JStringData::color;
}

void JSPosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Pos"), rect);
}

int JSPosObj::inputType(int n) { return JStringData::id;}
JString JSPosObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JSPosObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JStringData(v[n]));
  value = v[0].indexOf(v[1]);
  if (value != oldv) 
    broadcast(0);
}

