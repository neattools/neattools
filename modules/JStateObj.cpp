#include "JStateObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JStringProperty.h"
#include "JLinkObj.h"

#define MAXCOND 128
char* theJStateObj = JStateObj().Register();
void JStateObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putString(os, "name", name);
  putInteger(os, "state", state);
  putInteger(os, "N", N);
}

void JStateObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  name = getString(dict, "name");
  state = getInteger(dict, "state");
  N = getInteger(dict, "N");
  N = max(1, min(MAXCOND, N));
  igm = CONDITIONS+N;
  ogm = ACTIVATES+N;
}

const char* JStateObj::className() const { return "JStateObj";}
JObject* JStateObj::clone() const { return new JStateObj(*this);}

JStateObj::JStateObj() {
  N = 1;
  igm = CONDITIONS+N;
  ogm = ACTIVATES+N;
  name = "none";
  state = false;
  cond = JBlock(MAXCOND, 0);
}

void JStateObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, "State", rect1);
  drawText(g, name, rect2);
}

boolean JStateObj::outputAllowed(int n)
{ return (!n) ? true : !outputSet(n).last();}
boolean JStateObj::inputAllowed(int n)
{ return (!n) ? true : !inputSet(n).last();}


void JStateObj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (!n) INT(data) = state;
  else INT(data) = value;
}

JString JStateObj::inputTag(int n) {
  if (n == ENABLE) return "enable(logical)";
  else if (n == RESET) return "reset(logical)";
  return JString("condition-")+
    JInteger::toJString(n-CONDITIONS)+"(logical)";
}

JString JStateObj::outputTag(int n) {
  if (!n) return "state(logical)";
  return JString("activate-")+
   JInteger::toJString(n-ACTIVATES)+"(logical)";
}

JFRect JStateObj::inputArea(int n) { 
  if (n < RESET) return leftArea(n, 0, RESET);
  return topArea(n, RESET, igm-RESET);
}

JFRect JStateObj::outputArea(int n) { 
  if (!n) return bottomArea(n, 0, ACTIVATES);
  return rightArea(n, ACTIVATES, ogm-ACTIVATES);
}

int JStateObj::inputFace(int n) { 
  if (n < RESET) return LEFT;
  return TOP;
}

int JStateObj::outputFace(int n) { 
  if (!n) return BOTTOM;
  return RIGHT;
}

JFPoint JStateObj::inputPoint(int n, JLinkObj& link) { 
  if (n < RESET) return leftPoint(n, link, 0, RESET);
  return topPoint(n, link, RESET, igm-RESET);
}

JFPoint JStateObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return bottomPoint(n, link, 0, ACTIVATES);
  return rightPoint(n, link, ACTIVATES, ogm-ACTIVATES);
}

void JStateObj::updateN(int _N) {
  _N = max(1, min(MAXCOND, _N));
  if (N != _N) {
    JFRect rect = calculateInputUpdate();
    rect |= calculateOutputUpdate();
    N = _N;
    igm = CONDITIONS+N;
    ogm = ACTIVATES+N;
    rect |= calculateInputUpdate();
    rect |= calculateOutputUpdate();
    repaintView(rect);
  }
}

void JStateObj::resetBroadcast() {
  int i;
  value = 2;
  for (i=ACTIVATES; i<ogm; i++)
    broadcast(i);
  value = 0;
  for (i=ACTIVATES; i<ogm; i++)
    broadcast(i);
}

void JStateObj::engine(int n, JLinkObj& link) {
  if (n == ENABLE) {
    int enable = null;
    link.access(JIntegerData(enable));
    if (enable == 1) {
      state = mask;
      broadcast(STATE);
    } else if (enable == 2) {
      state = null;
      broadcast(STATE);
      resetBroadcast();
    }
  } else if (n == RESET) {
    int reset = null;
    link.access(JIntegerData(reset));
    if (reset) {
      resetBroadcast();
      state = mask;
      broadcast(STATE);
    }
  } else {
    if (!state) return;
    int oldCond = cond[n-=CONDITIONS];
    int condition = oldCond;
    link.access(JIntegerData(condition));
    condition = (condition != 0);
    if (condition != oldCond) {
      if (!condition) {
        state = false;
        broadcast(STATE);
        cs.lock();
        value = 1;
        broadcast(n+ACTIVATES);
        value = 0;
        broadcast(n+ACTIVATES);
        cs.unlock();
      }
      cond[n] = (char)condition;
    }
  }
}

JArray JStateObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("N", N, 1, MAXCOND));
  properties.append(JStringProperty("name", name));
  return properties;
}

boolean JStateObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("name")) {
    name = ((JStringProperty*)&prop)->value;
    repaint();
    return true;
  }
  return false;
}

