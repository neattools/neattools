#include "JNodeObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JLinkObj.h"

char* theJNodeObj = JNodeObj().Register();

const char* JNodeObj::className() const { return "JNodeObj";}
JObject* JNodeObj::clone() const { return new JNodeObj(*this);}

JNodeObj::JNodeObj() { 
  typeCounter = valueCounter = 0;
  eventIndicator = 0;
  ogm = 2;
}

void JNodeObj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (!n) {
    JLinkObj* prev = (JLinkObj*)inputSet(n).first();
    if (prev) {
      if (!valueCounter++) 
        prev->access(data);
      valueCounter--;
    }
  } else INT(data) = eventIndicator;
}

int JNodeObj::inputType(int n) {
  int type = JDataType::last;
  JLinkObj* link = (JLinkObj*)inputSet(n).first();
  if (link) {
    if (!typeCounter++)
      type = link->from->outputType(link->fn);
    typeCounter--;
  }
  if (type == JDataType::last) {
    link = (JLinkObj*)outputSet(n).first();
    if (link) {
      if (!typeCounter++)
        type = link->to->inputType(link->tn);
      typeCounter--;
    }
  }
  return type;
}

int JNodeObj::outputType(int n) 
{ return (!n) ? inputType(n) : JIntegerData::id;}
int JNodeObj::outputFace(int n) 
{ return (!n) ? RIGHT : BOTTOM;}

JString JNodeObj::outputTag(int n) {
  char* tag[] = {"ouput", "eventIndicator(logical)"};
  return tag[n];
}

JFRect JNodeObj::outputArea(int n) {
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, 1);
}

JFPoint JNodeObj::outputPoint(int n, JLinkObj& link) {
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, 1);
}

void JNodeObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/3;
  int dy = h/3;
  g.fillOval(x+dx, y+dy, dx, dy);
}

void JNodeObj::engine(int n, JLinkObj& link) { 
  eventIndicator = 1;
  broadcast(1);
  broadcast(n);
  eventIndicator = 0;
  broadcast(1);
}
