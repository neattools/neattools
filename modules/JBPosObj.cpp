#include "JBPosObj.h"
#include "JLinkObj.h"
#include "JBytesData.h"

char* theJBPosObj = JBPosObj().Register();
void JBPosObj::writeContent(JOutputStream& os) {
  JAbsObj::writeContent(os);
  putObject(os, "v0", v[0]);
  putObject(os, "v1", v[1]);
}

void JBPosObj::readContent(JDictionary& dict) {
  JAbsObj::readContent(dict);
  JObject *obj = getObject(dict, "v0");
  if (obj) v[0] = *(JBlock*)obj;
  obj = getObject(dict, "v1");
  if (obj) v[1] = *(JBlock*)obj;
}

const char* JBPosObj::className() const { return "JBPosObj";}
JObject* JBPosObj::clone() const { return new JBPosObj(*this);}
JBPosObj::JBPosObj() { 
  igm = 2;;
  moduleColor = JBytesData::color;
}

void JBPosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Pos"), rect);
}

int JBPosObj::inputType(int n) { return JBytesData::id;}
JString JBPosObj::inputTag(int n) { 
  char* tag[] = { "input-1", "input-2"};
  return tag[n];
}

void JBPosObj::engine(int n, JLinkObj& link) {
  int oldv = value;
  link.access(JBytesData(v[n]));
  value = v[0].indexOf(v[1]);
  if (value != oldv) 
    broadcast(0);
}

