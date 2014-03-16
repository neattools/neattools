#include "JJoyStickObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"
#if defined(WIN32)
  #include <windows.h>
#endif

char* theJJoyStickObj = JJoyStickObj().Register();
void JJoyStickObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "id", id);
}

void JJoyStickObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  id = getInteger(dict, "id");
  valid = isValid();
}

const char* JJoyStickObj::className() const { return "JJoyStickObj";}
JObject* JJoyStickObj::clone() const { return new JJoyStickObj(*this);}

char* joyTag[] = {"Joy1", "Joy2", null};

JJoyStickObj::JJoyStickObj(int _id) {
  id = _id;
  valid = isValid();
  clock = false;
  ogm = 10;
  for (int i=0; i<ogm; i++) v[i] = 0;
}

boolean JJoyStickObj::isValid() {
#if defined(WIN32)
  JOYINFO ji;
  if (!joyGetPos(id, &ji)) {
    JOYCAPS jc;
    joyGetDevCaps(id, &jc, sizeof(JOYCAPS));
  #if !defined(BC5)
    JOYINFOEX jiex;
    needEx = !joyGetPosEx(id, &jiex);
  #else
    needEx = false;
  #endif
    return true;
  }
  return false;
#else
  return false;
#endif
}

void JJoyStickObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect(x, y, w, h);
  drawText(g, joyTag[id], rect);
}

void JJoyStickObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = v[n];}

boolean JJoyStickObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JJoyStickObj::inputTag(int n) { return "sampling-clock(logical)";}

JString JJoyStickObj::outputTag(int n) {
  char* tag[] = { "X-pos", "Y-pos", "Z-pos",
    "R-pos", "U-pos", "V-pos",
    "Btn-1", "Btn-2", "Btn-3", "Btn-4"};
  return JString(tag[n])+NBTag();
}

JFRect JJoyStickObj::inputArea(int n) 
{ return topArea(n, 0, 1);}

JFRect JJoyStickObj::outputArea(int n) {
  if (n<6) return rightArea(n, 0, 6, 0, 1);
  return bottomArea(n, 6, 4);
}

int JJoyStickObj::inputFace(int n) { return TOP;}

int JJoyStickObj::outputFace(int n) {
  if (n<6) return RIGHT;
  return BOTTOM;
}

JFPoint JJoyStickObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, 1);}

JFPoint JJoyStickObj::outputPoint(int n, JLinkObj& link) {
  if (n<6) return rightPoint(n, link, 0, 6, 0, 1);
  return bottomPoint(n, link, 6, 4);
}

void JJoyStickObj::engine(int n, JLinkObj& link) {
  if (!valid) return;
  int oldClock = clock;
  link.access(JIntegerData(clock));
  clock = (clock != 0);
  if ((clock != oldClock) && clock) {
#if defined(WIN32)
    JOYINFO ji;
    joyGetPos(id, &ji);
    v[0] = matchNB(ji.wXpos, 16);
    broadcast(0);
    v[1] = matchNB(ji.wYpos, 16);
    broadcast(1);
    v[2] = matchNB(ji.wZpos, 16);
    broadcast(2);
    int bmask = JOY_BUTTON1;
    for (int i=0; i<4; i++) {
      v[i+6] = ((ji.wButtons & bmask) != 0) ? mask : 0;
      broadcast(i+6);
      bmask <<= 1;
    }
  #if !defined(BC5)
    if (needEx) {
      JOYINFOEX jiex;
      joyGetPosEx(id, &jiex);
      if (jiex.dwFlags & JOY_RETURNR) {
        v[3] = matchNB(jiex.dwRpos, 16);
        broadcast(3);
      } else v[3] = 0;
      if (jiex.dwFlags & JOY_RETURNU) {
        v[4] = matchNB(jiex.dwUpos, 16);
        broadcast(4);
      } else v[4] = 0;
      if (jiex.dwFlags & JOY_RETURNV) {
        v[5] = matchNB(jiex.dwVpos, 16);
        broadcast(5);
      } else v[5] = 0;
    }
  #endif
#endif
  }
}

JArray JJoyStickObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerListProperty("port", id, joyTag));
  return properties;
}

boolean JJoyStickObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("port")) {
    id = ((JIntegerListProperty*)&prop)->value;
    valid = isValid();
    repaint();
    return true;
  }
  return false;
}

void JJoyStickObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JJoyStickObj(0));
  addModuleButton(panel, JJoyStickObj(1));
}
