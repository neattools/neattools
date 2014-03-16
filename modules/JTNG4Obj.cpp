#include "JTNG4Obj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JBytesData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"

char* theJTNG4Obj = JTNG4Obj().Register();

void JTNG4Obj::writeContent(JOutputStream& os) {
  JTNG3Obj::writeContent(os);
  putInteger(os, "extraInputCount", extraInputCount);
  putInteger(os, "oseparator0", oseparators[0]);
  putInteger(os, "oseparator1", oseparators[1]);
}

void JTNG4Obj::readContent(JDictionary& dict) {
  JTNG3Obj::readContent(dict);
  extraInputCount = getInteger(dict, "extraInputCount");
  extraInputCount = max(0, min(32-IN_LAST, extraInputCount));
  igm = IN_LAST+extraInputCount;
  oseparators[0] = getInteger(dict, "oseparator0");
  oseparators[1] = getInteger(dict, "oseparator1");
}

const char* JTNG4Obj::className() const { return "JTNG4Obj";}
JObject* JTNG4Obj::clone() const { return new JTNG4Obj(*this);}

JTNG4Obj::JTNG4Obj() {
  int i;
  NB = 8;
  offset = 3;
  channelCount = 11;
  extraInputCount = 0;
  exclusive = true;
  igm = IN_LAST+extraInputCount;
  ogm = channelCount+offset;
  for (i=0; i<igm; i++) vi[i] = 0;
  osepCount = 0;
  oseparators[0] = 165;
  oseparators[1] = 90;
}

void JTNG4Obj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("TNG4"), rect);
}

void JTNG4Obj::access(int n, JLinkObj& link, const JDataType& data) { 
  if (n == OUT_COM) data.assign(buf);
  else INT(data) = v[n];
}

boolean JTNG4Obj::inputAllowed(int n) {
  switch (n) {
    case IN_C:
    case IN_CCONFIG:
      return 
        !inputSet(IN_A1).last() && !inputSet(IN_A2).last() &&
        !inputSet(IN_A3).last() && !inputSet(IN_A4).last();
    case IN_A1:
    case IN_A2:
    case IN_A3:
    case IN_A4:
       return !inputSet(IN_C).last() && 
	 !inputSet(IN_CCONFIG).last() ;
  }
  return true;
}

boolean JTNG4Obj::outputAllowed(int n) { 
  return true;
}

int JTNG4Obj::inputType(int n) { return (n == IN_COM) ? JBytesData::id : JIntegerData::id;}
int JTNG4Obj::outputType(int n) { return (n == OUT_COM) ? JBytesData::id : JIntegerData::id;}
int JTNG4Obj::inputFace(int n) { return (n < IN_BCONFIG) ? LEFT : TOP;}

JString JTNG4Obj::inputTag(int n) {
  if (n >= IN_LAST) {
    return JString("ExtraIn-")+
      JInteger::toJString(n-IN_LAST+1)+"(8Bits)";
  }
  char* tag[] = { "COM", 
    "A1(8Bits)", "A2(8Bits)", "A3(8Bits)", "A4(8Bits)",
    "B(8Bits)", "C(8Bits)", "D(8Bits)", 
    "Bconfig(8Bits)", "Cconfig(8Bits)", "Dconfig(8Bits)", 
    "sampling-clock(logical)"};
  return JString(tag[n]);
}

JString JTNG4Obj::outputTag(int n) {
  if (n < OUT_COM) {
    char* tag[] = { "Sync", "Clock"};
    return JString(tag[n])+NBTag();
  } if (n == OUT_COM) {
    return "COM";
  }
  return JString("ch-")+JInteger::toJString(n-2)+NBTag();
}

JFRect JTNG4Obj::inputArea(int n) { 
  if (n < IN_BCONFIG)
    return leftArea(n, 0, IN_BCONFIG);
  else return topArea(n, IN_BCONFIG, IN_LAST+extraInputCount-IN_BCONFIG);
}

JFPoint JTNG4Obj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_BCONFIG)
    return leftPoint(n, link, 0, IN_BCONFIG);
  else return topPoint(n, link, IN_BCONFIG, IN_LAST+extraInputCount-IN_BCONFIG);
}

JArray JTNG4Obj::getProperties() {
  JArray properties = JTNG3Obj::getProperties();
  properties.append(JIntegerProperty("oseparator0", oseparators[0], 0, 255));
  properties.append(JIntegerProperty("oseparator1", oseparators[1], 0, 255));
  properties.append(JIntegerListProperty("exclusive", exclusive, JIntegerListProperty::booleanTag));
  properties.append(JIntegerProperty("extraInputCount", extraInputCount, 0, 32-IN_LAST));
  return properties;
}

boolean JTNG4Obj::updateProperty(JProperty& prop) {
  if (prop.getName() == JString("oseparator0")) {
    oseparators[0] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("oseparator1")) {
    oseparators[1] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("exclusive")) {
    exclusive = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("extraInputCount")) {
    JFRect rect = calculateInputUpdate();
    extraInputCount = ((JIntegerProperty*)&prop)->value;
    igm = IN_LAST+extraInputCount;
    rect |= calculateInputUpdate();
    repaintView(rect);
    return true;
  } else if (JTNG3Obj::updateProperty(prop)) 
    return true;
  return false;
}

void JTNG4Obj::procCOM(uchar code) {
  cs.lock();
  static char* prefix = "ABCD";
  buf = JBlock(oseparators[osepCount])+
    JBlock(code);
  if (code & 1) buf += JBlock(prefix[1])+JBlock(vi[IN_BCONFIG])+JBlock(vi[IN_B]);
  if (code & 2) buf += JBlock(prefix[2])+JBlock(vi[IN_CCONFIG])+JBlock(vi[IN_C]);
  if (code & 4) buf += JBlock(prefix[3])+JBlock(vi[IN_DCONFIG])+JBlock(vi[IN_D]);
  if (code & 0xF0) {
    buf += JBlock(prefix[0]);
    if (code & 16) buf += JBlock(vi[IN_A1]);
    if (code & 32) buf += JBlock(vi[IN_A2]);
    if (code & 64) buf += JBlock(vi[IN_A3]);
    if (code & 128) buf += JBlock(vi[IN_A4]);
  }
  if (extraInputCount > 0)
    buf += JBlock(extraInputCount, vi+IN_LAST);
  osepCount = (osepCount+1)%2; 
  broadcast(OUT_COM);
  cs.unlock();
}

void JTNG4Obj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_COM: {
      JBlock data;
      link.access(JBlockData(data));
      int size = data.size();
      data.Dereference();
      for (int i=0; i<size; i++)
        processByte((uchar)data[i]);
      break;
    }
    case IN_A1: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_A1] = (char)(v & 0xFF);
	  if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(16);
      break;
    }
    case IN_A2: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_A2] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(32);
      break;
    }
    case IN_A3: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_A3] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(64);
      break;
    }
    case IN_A4: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_A4] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(128);
      break;
    }
    case IN_B: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_B] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(1);
      break;
    }
    case IN_C: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_C] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(2);
      break;
    }
    case IN_D: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_D] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) procCOM(4);
      break;
    }
    case IN_BCONFIG: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_BCONFIG] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last() && inputSet(IN_B).last()) procCOM(1);
      break;
    }
    case IN_CCONFIG: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_CCONFIG] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last() && inputSet(IN_C).last()) procCOM(2);
      break;
    }
    case IN_DCONFIG: {
      int v;
      link.access(JIntegerData(v));
      vi[IN_DCONFIG] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last() && inputSet(IN_D).last()) procCOM(4);
      break;
    }
    case IN_CLOCK: {
      int v;
      link.access(JIntegerData(v));
      v = (v != 0);
      if (v != vi[IN_CLOCK]) {
        vi[IN_CLOCK] = (char)v;
        if (v) {
          char code = 0;
          if (inputSet(IN_B).last() ||
            inputSet(IN_BCONFIG).last()) code |= 1;
          if (inputSet(IN_C).last() ||
            inputSet(IN_CCONFIG).last()) code |= 2;
          if (inputSet(IN_D).last() ||
            inputSet(IN_DCONFIG).last()) code |= 4;
          if (inputSet(IN_A1).last()) code |= 16;
          if (inputSet(IN_A2).last()) code |= 32;
          if (inputSet(IN_A3).last()) code |= 64;
          if (inputSet(IN_A4).last()) code |= 128;
          if (code) procCOM(code);
        }
      }
      break;
    }
    default: {
      int v;
      link.access(JIntegerData(v));
      vi[n] = (char)(v & 0xFF);
      if (!exclusive || !inputSet(IN_CLOCK).last()) 
	procCOM(0);
      break;
    }
  }
}

