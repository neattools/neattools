#include "JDelaySustainObj.h"
#include "JSystem.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJDelaySustainObj = JDelaySustainObj().Register();
void JDelaySustainObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "delay", delay);
  putInteger(os, "sustain", sustain);
}

void JDelaySustainObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  delay = getInteger(dict, "delay");
  sustain = getInteger(dict, "sustain");
}

const char* JDelaySustainObj::className() const { return "JDelaySustainObj";}
JObject* JDelaySustainObj::clone() const { return new JDelaySustainObj(*this);}

JDelaySustainObj::JDelaySustainObj() {
  igm = IN_LAST;
  ogm = OUT_LAST;
  counter = 0x80000000;
  edge = 0;
  mode = NONE;
  delay = sustain = 0;
  iv = 0;
  clock = 0;
}

void JDelaySustainObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("D/S"), rect);
}

boolean JDelaySustainObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JDelaySustainObj::access(int n, JLinkObj& link, const JDataType& data) {
  switch (n) {
    case OUT_DELAY: 
      INT(data) = delay;
      break;
    case OUT_SUSTAIN: 
      INT(data) = sustain;
      break;
    default:
      INT(data) = value;
  }
}

JString JDelaySustainObj::inputTag(int n) {
  char* tag[] = { "input", "sampling-clock(logical)", "delay", "sustain"};
  return tag[n];
}

JString JDelaySustainObj::outputTag(int n) {
  char* tag[] = { "output", "delay", "sustain"};
  return tag[n];
}

JFRect JDelaySustainObj::inputArea(int n) { 
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, IN_LAST-1);
}

JFRect JDelaySustainObj::outputArea(int n) { 
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, OUT_LAST-1);
}

int JDelaySustainObj::inputFace(int n) { 
  if (!n) return LEFT;
  return TOP;
}

int JDelaySustainObj::outputFace(int n) { 
  if (!n) return RIGHT;
  return BOTTOM;
}

JFPoint JDelaySustainObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, IN_LAST-1);
}

JFPoint JDelaySustainObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, OUT_LAST-1);
}

void JDelaySustainObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case INPUT : {
      int ov = iv;
      link.access(JIntegerData(iv));
      if (ov != iv) {
        cs.lock();
        if (iv != value) {
          if (iv > value) {
            if (!delay) {
              mode = NONE;
              value = iv;
              broadcast(0);
            } else {
              edge = counter;
              mode = DELAY_MODE;
            }
          } else {
            if (!sustain) {
              mode = NONE;
              value = iv;
              broadcast(0);
            } else {
              edge = counter;
              mode = SUSTAIN_MODE;
            }
          }
        }
        cs.unlock();
      }
      break;
    }
    case IN_CLOCK : {
      int oldClock = clock;
      link.access(JIntegerData(clock));
      clock = (clock != 0);
      if ((clock != oldClock) && clock) {
        cs.lock();
        counter++;
        if ((mode == DELAY_MODE) && (counter == edge+delay) ||
          (mode == SUSTAIN_MODE) && (counter == edge+sustain)) {
          value = iv;
          broadcast(0);
        }
        cs.unlock();
      }
      break;
    }
    case IN_DELAY : {
      int oDelay = delay;
      link.access(JIntegerData(delay));
      if (delay != oDelay) broadcast(OUT_DELAY);
      break;
    }
    case IN_SUSTAIN : {
      int oSustain = sustain;
      link.access(JIntegerData(sustain));
      if (sustain != oSustain) broadcast(OUT_SUSTAIN);
      break;
    }
  }
}

JArray JDelaySustainObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("delay", delay, 
    0, 65535));
  properties.append(JIntegerProperty("sustain", sustain, 
    0, 65535));
  return properties;
}

boolean JDelaySustainObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("delay")) {
    delay = ((JIntegerProperty*)&prop)->value;
    broadcast(OUT_DELAY);
    return true;
  } else if (prop.getName() == JString("sustain")) {
    sustain = ((JIntegerProperty*)&prop)->value;
    broadcast(OUT_SUSTAIN);
    return true;
  }
  return false;
}

