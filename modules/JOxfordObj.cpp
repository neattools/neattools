#include "JOxfordObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JBytesData.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJOxfordObj = JOxfordObj().Register();
int JOxfordObj::separator = 0x5a;

void JOxfordObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "factor", factor);
}

void JOxfordObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  factor = getInteger(dict, "factor");
  factor = max(1, min(256, factor));
}

const char* JOxfordObj::className() const { return "JOxfordObj";}
JObject* JOxfordObj::clone() const { return new JOxfordObj(*this);}

uchar revref[256] = {255};

JOxfordObj::JOxfordObj() {
  int i, j;
  factor = 1;
  sequence = 0;
  igm = 1;
  ogm = 8;
  last = 0;
  syncCount = 0;
  channel = 0;
  for (i=0; i<8; i++) 
    v[i] = 0;
  if (revref[0] == 255) {
    int val;
    for (i=0; i<256; i++) {
      val = 0;
      for (j=0; j<8; j++)
        val |= (((i>>j)&1)<<(7-j));
      revref[i] = val;
    }
  }
}

void JOxfordObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Oxford"), rect);
}

void JOxfordObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = v[n];}
int JOxfordObj::inputType(int n) { return JBytesData::id;}

JString JOxfordObj::inputTag(int n) { return "input";}
JString JOxfordObj::outputTag(int n) {
  char* tag[] = {
    "Sync", "Clock", 
    "PlRed", "PlRedIr", "ECG", 
    "Resp1", "Resp2", "Aux"
    };
  return JString(tag[n])+NBTag();
}

JFRect JOxfordObj::outputArea(int n) 
{ return rightArea(n, 0, ogm, 0, 1);}

JFPoint JOxfordObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, ogm, 0, 1);}

void JOxfordObj::processByte(int b) {
  channel++;
  if (v[0]) {
    if (channel == 64) {
      if (b != separator) {
	v[0] = 0;
	broadcast(0);
	return;
      }
    } else if (channel == 65) {
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
    switch (channel) {
      case -1: break;
      case 0: v[5] = (revref[b]<<8); break;
      case 1: 
	v[5] |= (revref[b]); 
	v[5] = 0x8000+(short)v[5];
        v[5] = matchNB(v[5], 16);
	break;
      case 2: v[6] = (revref[b]<<8); break;
      case 3: 
	v[6] |= (revref[b]); 
	v[6] = 0x8000+(short)v[6];
        v[6] = matchNB(v[6], 16);
	break;
      case 4: v[7] = (revref[b]<<8); break;
      case 5: 
	v[7] |= (revref[b]); 
	v[7] = 0x8000+(short)v[7];
        v[7] = matchNB(v[7], 16);
	break;
      case 6: 
      case 63:
      case 64: 
	break;
      default:
	switch (channel % 7) {
	  case 0: v[4] = (revref[b]<<8); break;
	  case 1: 
	    v[4] |= (revref[b]); 
	    v[4] = 0x8000+(short)v[4];
            v[4] = matchNB(v[4], 16);
	    break;
	  case 2: v[3] = (revref[b]<<8); break;
	  case 3: v[3] |= (revref[b]); break;
	  case 4: v[2] = (revref[b]<<8); break;
	  case 5: v[2] |= (revref[b]); break;
	  case 6: 
	    v[2] = 0x8000+(short)v[2];
	    v[3] = 0x8000+(short)v[3];
            v[2] = matchNB(v[2], 16);
            v[3] = matchNB(v[3], 16);
	    v[1] = 0;
	    broadcast(1);
	    broadcast(2);
	    broadcast(3);
	    broadcast(4);
	    broadcast(5); 
	    broadcast(6); 
	    broadcast(7); 
            v[1] = mask;
	    broadcast(1);
	    break;
	}
    }
    sequence = 0;
  } else {
    if (b == separator) {
      if (!syncCount) {
        syncCount++;
        last = b;
      } else {
        if (syncCount && (last == separator)) {
          channel = -1;
	  v[0] = mask;
	  broadcast(0);
        }
        syncCount = 0;
        last = 0;
      }
    }
  }
}

void JOxfordObj::engine(int n, JLinkObj& link) {
  JBlock data;
  link.access(JBlockData(data));
  int size = data.size();
  for (int i=0; i<size; i++)
    processByte((uchar)data[i]);
}

JArray JOxfordObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("factor", factor, 1, 256));
  return properties;
}

boolean JOxfordObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("factor")) {
    factor = ((JIntegerProperty*)&prop)->value;
    repaint();
    return true;
  }
  return false;
}

