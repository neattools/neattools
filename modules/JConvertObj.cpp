#include "JConvertObj.h"
#include "JColorProperty.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerListProperty.h"
#include "JDouble.h"
#include "JIntegerData.h"
#include "JBlockData.h"

char* theJConvertObj = JConvertObj().Register();

const char* JConvertObj::className() const { return "JConvertObj";}
JObject* JConvertObj::clone() const { return new JConvertObj(*this);}

JConvertObj::JConvertObj() {
  igm = JDataType::last;
  ogm = JDataType::last;
}

void JConvertObj::reset() { data.Dereference();}
void JConvertObj::startup() { data = JDataType::getDataArray();}
void JConvertObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Conv"), rect);
}

int JConvertObj::inputType(int n) { return n;}

int JConvertObj::outputType(int n) { return n;} 

void JConvertObj::access(int n, JLinkObj& link, const JDataType& _data) 
{ if (n < data.size()) _data.assign(*data[n]);}
boolean JConvertObj::inputAllowed(int n) { return true;}
boolean JConvertObj::outputAllowed(int n) { return true;}

JString JConvertObj::inputTag(int n) {
  return JString(JDataType::tag[n])+"-in";
}

JString JConvertObj::outputTag(int n) {
  return JString(JDataType::tag[n])+"-out";
}

JFRect JConvertObj::inputArea(int n) { 
  if (!n) return topArea(n, 0, 1);
  return leftArea(n, 1, igm-1, 0, 1);
}

JFRect JConvertObj::outputArea(int n) { 
  if (!n) return bottomArea(n, 0, 1);
  return rightArea(n, 1, igm-1, 0, 1);
}

int JConvertObj::inputFace(int n) 
{ return (!n) ? TOP : LEFT;}

int JConvertObj::outputFace(int n) 
{ return (!n) ? BOTTOM : RIGHT;}

JFPoint JConvertObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return topPoint(n, link, 0, 1);
  return leftPoint(n, link, 1, igm-1, 0, 1);
}

JFPoint JConvertObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return bottomPoint(n, link, 0, 1);
  return rightPoint(n, link, 1, igm-1, 0, 1);
}		     

void JConvertObj::engine(int n, JLinkObj& link) {
  if (n >= data.size()) return;
  cs.lock();
  JObject *obj = JDataType::create(n, link);
  if (n == JBlockData::id) {
    int id;
    JObject *item = JDataType::createTag(id, *(JBlock*)obj);
    if (item) {
      data.set(id, *item);
      broadcast(id);
      delete item;
    }
  } else {
    *(JBlock*)data[JBlockData::id]
      = JDataType::toTagBlock(n, *obj);
    broadcast(JBlockData::id);
  }
  delete obj;
  cs.unlock();
}

