#include "JTNGObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JBytesData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"

char* theJTNGObj = JTNGObj().Register();
uchar JTNGObj::separator = 255;

void JTNGObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "factor", factor);
  putInteger(os, "channelCount", channelCount);
  for (int i=0; i<channelCount; i++) 
    putInteger(os, JString("inv-")+
      JInteger::toJString(i+1), inv[i]);
}

void JTNGObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  factor = getInteger(dict, "factor");
  channelCount = getInteger(dict, "channelCount");
  factor = max(1, min(256, factor));
  channelCount = max(4, min(32, channelCount));
  ogm = channelCount+offset;
  for (int i=0; i<channelCount; i++) 
    inv[i] = getInteger(dict, JString("inv-")+
      JInteger::toJString(i+1));
}

const char* JTNGObj::className() const { return "JTNGObj";}
JObject* JTNGObj::clone() const { return new JTNGObj(*this);}

JTNGObj::JTNGObj() {
  int i;
  offset = 2;
  factor = 16;
  sequence = 0;
  channel = 0;
  channelCount = 4;
  igm = 1;
  ogm = channelCount+offset;
  for (i=0; i<MAX_CHANNEL; i++) inv[i] = false;
  for (i=0; i<MAX_CHANNEL+3; i++) v[i] = 0;
}

void JTNGObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("TNG"), rect);
}

void JTNGObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = v[n];}
int JTNGObj::inputType(int n) { return JBytesData::id;}

JString JTNGObj::inputTag(int n) { return "input";}
JString JTNGObj::outputTag(int n) {
  if (n < 2) {
    char* tag[] = { "Sync", "Clock"};
    return JString(tag[n])+NBTag();
  }
  return JString("ch-")+JInteger::toJString(n-1)+NBTag();
}

JFRect JTNGObj::outputArea(int n) 
{ return rightArea(n, 0, ogm, 0, 1);}
JFPoint JTNGObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, ogm, 0, 1);}

void JTNGObj::processByte(int b) {
  channel++;
  if (v[0]) {
    if (channel >= channelCount) {
      if (b != separator) {
	v[0] = 0;
	broadcast(0);
	return;
      } else {
	sequence++;
        channel = -1;
      }
    }
    if (sequence%factor) return;
    if (channel > -1) {
      b = matchNB(b, 8);
      if (inv[channel])
	v[channel+offset] = mask-b;
      else v[channel+offset] = b;
      broadcast(channel+offset);
    } else {
      v[1] = mask; 
      broadcast(1);
      v[1] = 0; 
      broadcast(1);
    }
    sequence = 0;
  } else {
    if (b == separator) {
      channel = -1;
      v[0] = mask;
      broadcast(0);
    }
  }
}

void JTNGObj::engine(int n, JLinkObj& link) {
  JBlock data;
  link.access(JBlockData(data));
  int size = data.size();
  data.Dereference();
  for (int i=0; i<size; i++)
    processByte((uchar)data[i]);
}

JArray JTNGObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("factor", factor, 1, 256));
  properties.append(JIntegerProperty("channelCount", channelCount, 4, 32));
  for (int i=0; i<channelCount; i++) 
    properties.append(JIntegerListProperty(
      JString("inv-")+JInteger::toJString(i+1), 
      inv[i], JIntegerListProperty::booleanTag));
  return properties;
}

boolean JTNGObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("factor")) {
    factor = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("channelCount")) {
    JFRect rect = calculateOutputUpdate();
    channelCount = ((JIntegerProperty*)&prop)->value;
    ogm = channelCount+offset;
    rect |= calculateOutputUpdate();
    repaintView(rect);
    return true;
  } else for (int i=0; i<channelCount; i++) {
    if (prop.getName() == JString("inv-")+JInteger::toJString(i+1)) {
      inv[i] = ((JIntegerListProperty*)&prop)->value;
      return true;
    }
  }
  return false;
}

