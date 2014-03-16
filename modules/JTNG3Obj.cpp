#include "JTNG3Obj.h"
#include "JInteger.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJTNG3Obj = JTNG3Obj().Register();

void JTNG3Obj::writeContent(JOutputStream& os) {
  JTNGObj::writeContent(os);
  putInteger(os, "separator0", separators[0]);
  putInteger(os, "separator1", separators[1]);
}

void JTNG3Obj::readContent(JDictionary& dict) {
  JTNGObj::readContent(dict);
  separators[0] = getInteger(dict, "separator0");
  separators[1] = getInteger(dict, "separator1");
}

const char* JTNG3Obj::className() const { return "JTNG3Obj";}
JObject* JTNG3Obj::clone() const { return new JTNG3Obj(*this);}

JTNG3Obj::JTNG3Obj() {
  channelCount = 9;
  ogm = channelCount+offset;
  sepCount = 0;
  separators[0] = 170;
  separators[1] = 85;
}

void JTNG3Obj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("TNG3"), rect);
}

void JTNG3Obj::processByte(int b) {
  channel++;
  if (v[0]) {
    if (channel >= channelCount) {
      if (b != separators[sepCount]) {
    	v[0] = 0;
	broadcast(0);
	return;
      } else {
        sepCount = (++sepCount)%2;
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
    if (b == separators[sepCount]) {
      sepCount = (++sepCount)%2;
      channel = -1;
      v[0] = mask;
      broadcast(0);
    }
  }
}

JArray JTNG3Obj::getProperties() {
  JArray properties = JTNGObj::getProperties();
  properties.append(JIntegerProperty("separator0", separators[0], 0, 255));
  properties.append(JIntegerProperty("separator1", separators[1], 0, 255));
  return properties;
}

boolean JTNG3Obj::updateProperty(JProperty& prop) {
  if (prop.getName() == JString("separator0")) {
    separators[0] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("separator1")) {
    separators[1] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (JTNGObj::updateProperty(prop)) 
    return true;
  return false;
}

