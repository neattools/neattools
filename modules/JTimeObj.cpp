#include "JTimeObj.h"
#include "JLinkObj.h"
#include "JDateData.h"
#include "JIntegerData.h"

char* theJTimeObj = JTimeObj().Register();
const char* JTimeObj::className() const { return "JTimeObj";}
JObject* JTimeObj::clone() const { return new JTimeObj(*this);}

JTimeObj::JTimeObj() {
  valid = false;
  igm = IN_LAST;
  ogm = 1;
  updateTime();
}

JTimeObj::~JTimeObj() { 
  close();
}

void JTimeObj::run() {
  valid = true;
  updateTime();
  while (valid && !inputSet(0).last()) {
    while (!isTimeChanged() && valid)
      JThread::sleep(10);
    updateTime();
    broadcast(0);
    if (!valid) break;
    JThread::sleep(900);
  }
}

void JTimeObj::delInput(int n, class JLinkObj& link) {
  JModuleObj::delInput(n, link);
  if (!inputSet(0).last()) startup();
}

void JTimeObj::delAllInput(int n) {
  JModuleObj::delAllInput(n);
  if (!inputSet(0).last()) startup();
}

void JTimeObj::reset() { valid = false;}

void JTimeObj::startup() {
  thread = JThread(this);
  thread.start();
}

void JTimeObj::close() {
  if (!valid) return;
  valid = false;
}

boolean JTimeObj::isTimeChanged() {
  updateTime();
  return (oldd.getSeconds() != date.getSeconds());
}

void JTimeObj::updateTime() {
  oldd = date;
  date = JDate();
}

void JTimeObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Time"), rect);
}

void JTimeObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(date);}

boolean JTimeObj::inputAllowed(int n)
{ return !inputSet(n).last();}
boolean JTimeObj::outputAllowed(int n)
{ return true;}

int JTimeObj::outputType(int n) { return JDateData::id;}

JString JTimeObj::inputTag(int n) {
  return "trigger(logical)";
}

JFRect JTimeObj::inputArea(int n) { 
  return topArea(n, 0, IN_LAST);
}

int JTimeObj::inputFace(int n) { 
  return TOP;
}

JFPoint JTimeObj::inputPoint(int n, JLinkObj& link) { 
  return topPoint(n, link, 0, IN_LAST);
}

void JTimeObj::engine(int n, JLinkObj& link) {
  if (n == IN_TRIGGER) {
    int iv;
    link.access(JIntegerData(iv));
    if (iv != 0) {
      updateTime();
      broadcast(0);
    }
  }
}

