#include "JWtoIObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JWaveData.h"
#include "JWaveOutObj.h"
#include "JWindow.hpp"

char* theJWtoIObj = JWtoIObj().Register();

void JWtoIObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "samplingFactor", samplingFactor);
}

void JWtoIObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  samplingFactor = getInteger(dict, "samplingFactor", 32);
  samplingFactor = max(1, min(512, samplingFactor));
}

const char* JWtoIObj::className() const { return "JWtoIObj";}
JObject* JWtoIObj::clone() const { return new JWtoIObj(*this);}

JWtoIObj::JWtoIObj() { 
  ogm = 2;
  moduleColor = JWaveData::color; 
  samplingFactor = 32;
}

int JWtoIObj::inputType(int n) { return JWaveData::id;}

void JWtoIObj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (!n) INT(data) = value;
  else INT(data) = right;
}

JString JWtoIObj::outputTag(int n) { 
  char* tag[] = {"outputL/Mono(16bits)", "outputR(16bits)"};
  return tag[n];
}

JFRect JWtoIObj::outputArea(int n) 
{ return rightArea(n, 0, ogm);}
JFPoint JWtoIObj::outputPoint(int n, JLinkObj& link)
{ return rightPoint(n, link, 0, ogm);}

void JWtoIObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("WtoI"), rect);
}

void JWtoIObj::engine(int n, JLinkObj& link) {
#if defined(WIN32)
  JBlock data;
  link.access(JBlockData(data));
  if (data.size() < sizeof(WAVEHDR)) return;
  data.Dereference();
  WAVEHDR *whdr = (WAVEHDR*)(char*)data;
  ushort nid = HIWORD(whdr->dwUser) & 0xF;
  int frequency = JWaveOutObj::frequencyValue[nid];
  int channel = JWaveOutObj::channelValue[nid];
  int bits = JWaveOutObj::bitsValue[nid];
  int length = whdr->dwBufferLength;
  char* buf = (char*)(whdr+1);
  int factor = samplingFactor*channel*bits/8;
  if (nid >= JWaveOutObj::_LAST) return;
  if (bits == 8) {
    for (int i=0; i<length; i+=factor) {
      value = ((short)buf[i])<<8;
      broadcast(0);
      if (channel == 2) {
        right = ((short)buf[i+1])<<8;
        broadcast(1);
      }
    }
  } else {
    for (int i=0; i<length; i+=factor) {
      value = *(short*)(buf+i);
      broadcast(0);
      if (channel == 2) {
        right = *(short*)(buf+i+2);
        broadcast(1);
      }
    }
  }
#endif
}

JArray JWtoIObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("samplingFactor", samplingFactor, 1, 512));
  return properties;
}

boolean JWtoIObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("samplingFactor")) {
    samplingFactor = ((JIntegerProperty*)&prop)->value;
    return true;
  }
  return false;
}

