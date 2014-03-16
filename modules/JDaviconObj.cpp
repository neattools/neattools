#include "JDaviconObj.h"
#include "JMath.h"
#include "JThread.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JRealData.h"
#include "JBytesData.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"

#if defined(WIN32)
  #include "JWindow.hpp"
  #include <conio.h>
  #if !defined(BC5)
    #define HASPORTIO
  #endif
#endif

char* theJDaviconObj = JDaviconObj().Register();

double JDaviconObj::EMGFactor = 0.1;
double JDaviconObj::EMGConstant = JMath::log(1.0005623);
double JDaviconObj::PPGFactor = 1638.3;
double JDaviconObj::PPGConstant = 0.0;
double JDaviconObj::TRFactor = 400.0;
double JDaviconObj::TRConstant = 59.04;
double JDaviconObj::TSFactor = 400.0;
double JDaviconObj::TSConstant = 59.04;
double JDaviconObj::SCLFactor = 0.485;
double JDaviconObj::SCLConstant = JMath::log(1.000354);
double JDaviconObj::SCRFactor = 163.83;
double JDaviconObj::SCRConstant = 0.0;

void JDaviconObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "id", id);
  putInteger(os, "port", port);
}

void JDaviconObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  id = getInteger(dict, "id");
  port = getInteger(dict, "port");
  valid = check();
}

const char* JDaviconObj::className() const { return "JDaviconObj";}
JObject* JDaviconObj::clone() const { return new JDaviconObj(*this);}

char* portTag[] = {
  "0x280",
  "0x290",
  "0x2A0",
  null
};

int portValue[] = {
  0x280,
  0x290,
  0x2A0
};

enum { EMG, TEMP, SCL, PPG, SCR, TR, TS, NONE};

char* channelTag[] = {
  "EMG(MicroVolts)", 
  "TEMP(Degrees Fahrenheit)", 
  "SCL(MicroSiemens/square centimeter)", 
  "PPG", 
  "SCR", 
  "T/R", 
  "T/S", 
  "NONE"};

int config[9][8] = {
  {NONE, NONE, SCL, SCR, EMG, TR, EMG, TR},
  {TS, TS, EMG, EMG, EMG, EMG, EMG, EMG},
  {EMG, EMG, NONE, NONE, NONE, NONE, NONE, NONE},
  {PPG, TR, SCL, SCR, EMG, TR, EMG, TR},
  {PPG, TR, SCL, TR, EMG, EMG, EMG, EMG},
  {PPG, TR, SCL, SCR, EMG, NONE, EMG, NONE},
  {EMG, NONE, EMG, NONE, EMG, NONE, EMG, NONE},
  {EMG, EMG, EMG, EMG, EMG, EMG, EMG, EMG},
  {TR, TR, SCL, SCR, EMG, EMG, EMG, EMG}
};

char* deviceTag[] = {
  "Biofeedback System/3 (BIOFEED)",
  "Clinical Interface Pac (CIP)",
  "Dual Interface Pac (DIP)",
  "MEDAC System/3 (MEDAC)",
  "MEDAC System/3R (MEDR)",
  "MEDAC 3000 (MEDX)",
  "Neuromuscular System/3 (NM)",
  "Neuromuscular System/3D (NM8)",
  "Rehab System/3 (REHAB)",
  null
};

JDaviconObj::JDaviconObj() {
  id = 0;
  port = 0;
  igm = 2;
  ogm = 8;
  connected = false;
  valid = check();
  enabled = false;
  for (int i=0; i<8; i++) 
    v[i] = 0;
}

JDaviconObj::~JDaviconObj() { close();}

void JDaviconObj::reset() { connected = false;}

void JDaviconObj::open() {
  if (!valid || connected) return;
  int addr = portValue[port];
#if defined(HASPORTIO)
  if (JMicroSoft::isWinNT()) return;
  _outp(addr+2, 0x3C);
  connected = true;
  repaint();
#endif
}

void JDaviconObj::close() {
  if (!valid || !connected) return;
  int addr = portValue[port];
#if defined(HASPORTIO)
  if (JMicroSoft::isWinNT()) return;
  _outp(addr+2, 0);
  connected = false;
  repaint();
#endif
}

void JDaviconObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JDaviconObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("Davicn"), rect1);
  drawText(g, deviceTag[id], rect2);
}

void JDaviconObj::access(int n, JLinkObj& link, const JDataType& data) 
{ DOUBLE(data) = v[n];}

int JDaviconObj::outputType(int n) { return JRealData::id;}

JString JDaviconObj::inputTag(int n) { 
  char* tag[] = {"enabled(logical)",
    "sampleClock(logical)"};
  return tag[n];
}

JString JDaviconObj::outputTag(int n) 
{ return JString(channelTag[config[id][n]]);}

int JDaviconObj::inputFace(int n) { return TOP;}

JFRect JDaviconObj::inputArea(int n) 
{ return topArea(n, 0, igm);}

JFPoint JDaviconObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, igm);}

JFRect JDaviconObj::outputArea(int n) 
{ return rightArea(n, 0, ogm, 0, 1);}

JFPoint JDaviconObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, ogm, 0, 1);}

void JDaviconObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int oldEnabled = enabled;
    link.access(JIntegerData(enabled));
    enabled = (enabled != 0);
    if (enabled != oldEnabled) {
      if (enabled) open();
      else close();
    }
    return;
  }
  if (!connected) return;
  int iv;
  link.access(JIntegerData(iv));
  if (iv != 0) {
    for (int i=0; i<8; i++) {
      switch (config[id][i]) {
        case EMG:
          v[i] = JMath::exp(EMGConstant*sample(i))*EMGFactor;
          break;
        case SCL:
          v[i] = JMath::exp(SCLConstant*sample(i))*SCLFactor;
          break;
        case PPG:
          v[i] = double(sample(i))/PPGFactor+PPGConstant;
          break;
        case SCR:
          v[i] = double(sample(i))/SCRFactor+SCRConstant;
          break;
        case TR:
          v[i] = double(sample(i))/TRFactor+TRConstant;
          break;
        case TS:
          v[i] = double(sample(i))/TSFactor+TSConstant;
          break;
        default:
          v[i] = 0.0;
      }
      broadcast(i);
    }
  }
}

JArray JDaviconObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("id", id, deviceTag));
  properties.append(JIntegerListProperty("port", port, portTag));
  return properties;
}

boolean JDaviconObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("id")) {
    id = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("port")) {
    if (enabled) close();
    port = ((JIntegerListProperty*)&prop)->value;
    valid = check();
    if (enabled) open();
    repaint();
    return true;
  }
  return false;
}

int JDaviconObj::sample(int channel) {
  int result = -1;
#if defined(HASPORTIO)
  if (JMicroSoft::isWinNT()) return result;
  int addr = portValue[port];
  _outp(addr+4, channel);
  JThread::sleep(1);
  _outp(addr+1, 0);
  do {
    JThread::sleep(1);
    result = _inp(addr+1);
  } while (!(result & 0x80));
  if (result & 0x40) return 0;
  return ((result & 0x3F)<<8)+_inp(addr);
#else  
  return result;
#endif
}

boolean JDaviconObj::check() {
#if defined(HASPORTIO)
  if (JMicroSoft::isWinNT()) return false;
  int addr = portValue[port]+6;
  int counter = 0;
  int v = _inp(addr) & 0x01;
  for (int i=0; i<10; i++) {
    JThread::sleep(1);
    if (v != (_inp(addr) & 0x01)) {
      v = !v;
      counter++;
    }
  }
  return (counter != 0);
#else  
  return false;
#endif
}
