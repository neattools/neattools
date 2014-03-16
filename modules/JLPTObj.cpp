#include "JLPTObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"

/*
#if defined(WIN32)
  #include "JWindow.hpp"
  #include <conio.h>
  #if !defined(BC5)
    #define HASPORTIO
  #endif
#endif

char* theJLPTObj = JLPTObj().Register();
char* addrTag[] = { 
  "LPT1 (0x378)", 
  "LPT2 (0x278)", 
  "LPT3 (0x3bc)", 
  null};
int addr[] = { 0x378, 0x278, 0x3bc};

void JLPTObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "id", id);
}

void JLPTObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  id = getInteger(dict, "id");
  id = max(0, min(2, id));
  port = addr[id];
  valid = isValid();
}

const char* JLPTObj::className() const { return "JLPTObj";}
JObject* JLPTObj::clone() const { return new JLPTObj(*this);}

JLPTObj::JLPTObj(int _id) {
  id = _id;
  port = addr[id];
  clock = false;
  igm = 3;
  valid = isValid();
}

boolean JLPTObj::isValid() {
#if defined(HASPORTIO)
  if (JMicroSoft::isWinNT()) return false;
  _outp(port, 0xff);
  _outp(port, 0x00);
  return (_inp(port) == 0x00);
#else
  return false;
#endif
}

void JLPTObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("Lpt"), rect1);
  drawText(g, JString("0x")+JInteger::toJString(port, 16), rect2);
}

boolean JLPTObj::inputAllowed(int n)
{ return (boolean)((n == 1) ? !inputSet(n).last() : true);}

JString JLPTObj::inputTag(int n) {
  char* tag[] = { "input(8 bits)", "sampling-clock(logical)", "control(8 bits)"};
  return tag[n];
}

JString JLPTObj::outputTag(int n) {
  return "status(5 bits)";
}

JFRect JLPTObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, 2);
}

JFPoint JLPTObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, 2);
}

void JLPTObj::engine(int n, JLinkObj& link) {
  if (!valid) return;
  if (!n) {
#if defined(HASPORTIO)
    int ivalue;
    link.access(JIntegerData(ivalue));
    _outp(port, (ushort)ivalue);
#endif
  } else if (n == 1) {
    int oldClock = clock;
    link.access(JIntegerData(clock));
    clock = (clock != 0);
    if ((clock != oldClock) && clock) {
#if defined(HASPORTIO)
      value = (_inp(port+1)^0x80)>>3;
      broadcast(0);
#endif
    }
  } else {
#if defined(HASPORTIO)
    int ivalue;
    link.access(JIntegerData(ivalue));
    _outp(port+2, (ushort)(ivalue^0xb));
#endif
  }
}

JArray JLPTObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("port", id, addrTag));
  return properties;
}

boolean JLPTObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("port")) {
    id = ((JIntegerListProperty*)&prop)->value;
    port = addr[id];
    valid = isValid();
    repaint();
    return true;
  }
  return false;
}

void JLPTObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JLPTObj(0));
  addModuleButton(panel, JLPTObj(1));
  addModuleButton(panel, JLPTObj(2));
}
*/

#if defined(WIN32)
  #include "JWindow.hpp"
  #define HASPORTIO
  typedef void (WINAPI *POut32)(short, short);
  typedef short (WINAPI *PInp32)(short);
  DllImport POut32 Out32;
  DllImport PInp32 Inp32;
#endif

char* theJLPTObj = JLPTObj().Register();
char* addrTag[] = { 
  "LPT1 (0x378)", 
  "LPT2 (0x278)", 
  "LPT3 (0x3bc)", 
  null};
int addr[] = { 0x378, 0x278, 0x3bc};

void JLPTObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "id", id);
}

void JLPTObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  id = getInteger(dict, "id");
  id = max(0, min(2, id));
  port = addr[id];
}

const char* JLPTObj::className() const { return "JLPTObj";}
JObject* JLPTObj::clone() const { return new JLPTObj(*this);}

JLPTObj::JLPTObj(int _id) {
  id = _id;
  port = addr[id];
  clock = false;
  igm = 4;
  enabled = false;
  connected = false;
}

boolean JLPTObj::isValid() {
#if defined(HASPORTIO)
  if ((Out32 == NULL) || (Inp32 == NULL)) return false;
  Out32(port, 0xff);
  Out32(port, 0x00);
  return (Inp32(port) == 0x00);
#else
  return false;
#endif
}

void JLPTObj::reset() {
  connected = false;
}

void JLPTObj::close() {
  if (!connected) return;
  connected = false;
  repaint();
}

void JLPTObj::open() {
  if (connected) return;
  if (isValid()) {
    connected = true;
    repaint();
    return;
  }
}

void JLPTObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JLPTObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("Lpt"), rect1);
  drawText(g, JString("0x")+JInteger::toJString(port, 16), rect2);
}

boolean JLPTObj::inputAllowed(int n)
{ return (boolean)((n == SAMPLING) ? !inputSet(n).last() : true);}

JString JLPTObj::inputTag(int n) {
  char* tag[] = { "input(8 bits)", "enabled(logical)", "sampling-clock(logical)", "control(8 bits)"};
  return tag[n];
}

JString JLPTObj::outputTag(int n) {
  return "status(5 bits)";
}

JFRect JLPTObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, IN_LAST-1);
}

JFPoint JLPTObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, IN_LAST-1);
}

void JLPTObj::engine(int n, JLinkObj& link) {
  if (n == ENABLED) {
    link.access(JIntegerData(enabled));
    if (enabled) open();
    else close();
    return;
  }
  if (!connected) return;
  if (n == INPUT) {
#if defined(HASPORTIO)
    int ivalue;
    link.access(JIntegerData(ivalue));
    Out32(port, (ushort)ivalue);
#endif
  } else if (n == SAMPLING) {
    int oldClock = clock;
    link.access(JIntegerData(clock));
    clock = (clock != 0);
    if ((clock != oldClock) && clock) {
#if defined(HASPORTIO)
      value = (Inp32(port+1)^0x80)>>3;
      broadcast(0);
#endif
    }
  } else if (n == CONTROL) {
#if defined(HASPORTIO)
    int ivalue;
    link.access(JIntegerData(ivalue));
    Out32(port+2, (ushort)(ivalue^0xb));
#endif
  }
}

JArray JLPTObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("port", id, addrTag));
  return properties;
}

boolean JLPTObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("port")) {
    if (enabled) close();
    id = ((JIntegerListProperty*)&prop)->value;
    port = addr[id];
    if (enabled) open();
    repaint();
    return true;
  }
  return false;
}

void JLPTObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JLPTObj(0));
  addModuleButton(panel, JLPTObj(1));
  addModuleButton(panel, JLPTObj(2));
}
