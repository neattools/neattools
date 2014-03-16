#include "JRCalibrateObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JRealData.h"
#include "JRealProperty.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJRCalibrateObj = JRCalibrateObj().Register();
void JRCalibrateObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putDouble(os, "lower", lower);
  putDouble(os, "upper", upper);
  putInteger(os, "calibrating", calibrating);
  putInteger(os, "fraction", fraction);
}

void JRCalibrateObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  lower = getDouble(dict, "lower");
  upper = getDouble(dict, "upper");
  calibrating = getInteger(dict, "calibrating");
  fraction = getInteger(dict, "fraction");
  fraction = max(0, min(98, fraction));
  calculateLimits();
}

const char* JRCalibrateObj::className() const { return "JRCalibrateObj";}
JObject* JRCalibrateObj::clone() const { return new JRCalibrateObj(*this);}

JRCalibrateObj::JRCalibrateObj() {
  igm = IN_LAST+1;
  ogm = IN_LAST;
  lower = upper = 0.0;
  lowerLimit = upperLimit = 0.0;
  ivalue = 0.0;
  calibrating = false;
  fraction = 0;
  moduleColor = JRealData::color;
}

void JRCalibrateObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JANDObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (calibrating) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JRCalibrateObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int dy = h/5;
  int by = (h-dy*3)/2;
  int mx = w/2;
  g.drawLine(x+bx, y+by+dy, x+bx+dx*3, y+by+dy);
  g.drawLine(x+bx, y+by+dy*2, x+bx+dx*3, y+by+dy*2);
  g.drawLine(x+bx+dx, y+by+dy*3, x+mx, y+by+dy*3);
  g.drawLine(x+mx, y+by+dy*3, x+mx, y+by);
  g.drawLine(x+mx, y+by, x+bx+dx*2, y+by);
}

boolean JRCalibrateObj::inputAllowed(int n)
{ return !inputSet(n).last();}

void JRCalibrateObj::access(int n, JLinkObj& link, const JDataType& data) {
  switch (n) {
    case LOWER: 
      DOUBLE(data) = lower;
      break;
    case UPPER: 
      DOUBLE(data) = upper;
      break;
    case CALIBRATE:
      DOUBLE(data) = decalibrate;
      break;
    default:
      INT(data) = value;
  }
}

JString JRCalibrateObj::inputTag(int n) {
  char* tag[] = { "input", "calibrate(logical)", "lower", "upper", "feedback"};
  if (n == IN_LAST) return JString(tag[n])+NBTag();
  return tag[n];
}

JString JRCalibrateObj::outputTag(int n) {
  char* tag[] = { "output", "decalibrate", "lower", "upper"};
  if (!n) return JString(tag[n])+NBTag();
  return tag[n];
}

int JRCalibrateObj::inputType(int n) {
  switch (n) {
    case INPUT:
    case LOWER:
    case UPPER:
      return JRealData::id;
  }
  return JIntegerData::id;
}

int JRCalibrateObj::outputType(int n) {
  switch (n) {
    case CALIBRATE:
    case LOWER:
    case UPPER:
      return JRealData::id;
  }
  return JIntegerData::id;
}

JFRect JRCalibrateObj::inputArea(int n) { 
  if (!n) return leftArea(n, 0, 1, 0.25, 0.25);
  if (n == IN_LAST) return leftArea(n, IN_LAST, 1, 0.5, 0.25);
  return topArea(n, 1, IN_LAST-1);
}

JFRect JRCalibrateObj::outputArea(int n) { 
  if (n < 2) return rightArea(n, 0, 2);
  return bottomArea(n, 2, 2);
}

int JRCalibrateObj::inputFace(int n) { 
  if ((!n) || (n == IN_LAST)) return LEFT;
  return TOP;
}

int JRCalibrateObj::outputFace(int n) { 
  if (n < 2) return RIGHT;
  return BOTTOM;
}

JFPoint JRCalibrateObj::inputPoint(int n, JLinkObj& link) { 
  if (!n) return leftPoint(n, link, 0, 1, 0.25, 0.25);
  if (n == IN_LAST) return leftPoint(n, link, IN_LAST, 1, 0.5, 0.25);
  return topPoint(n, link, 1, IN_LAST-1);
}

JFPoint JRCalibrateObj::outputPoint(int n, JLinkObj& link) { 
  if (n < 2) return rightPoint(n, link, 0, 2);
  return bottomPoint(n, link, 2, 2);
}

void JRCalibrateObj::calculateLimits() {
  double delta = 0;
  if (lower != upper)
    delta = (upper-lower)*fraction/(100-fraction);
  lowerLimit = lower-delta;
  upperLimit = upper+delta;
}

void JRCalibrateObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case INPUT : {
      link.access(JRealData(ivalue));
      if (calibrating) {
        if (ivalue < lower) {
	  lower = ivalue;
          calculateLimits();
	  broadcast(LOWER);
        }
        if (ivalue > upper) {
	  upper = ivalue;
	  calculateLimits();
	  broadcast(UPPER);
        }
      }
      if (lower != upper) {
        if (!calibrating) {
          if (ivalue < lowerLimit) ivalue = lowerLimit;
          if (ivalue > upperLimit) ivalue = upperLimit;
        }
        value = (int)((ivalue-lowerLimit)*
	  mask/(upperLimit-lowerLimit));
      } else value = (int)ivalue;
      broadcast(INPUT);
      break;
    }
    case CALIBRATE : {
      int oldv = calibrating;
      link.access(JIntegerData(calibrating));
      if (oldv != calibrating) {
        if (calibrating) {
          lower = upper = ivalue;
	  calculateLimits();
	  broadcast(LOWER);
	  broadcast(UPPER);
        }
        repaint();
      }
      break;
    }
    case LOWER : {
      double oLower = lower;
      link.access(JRealData(lower));
      if (oLower != lower) {
        calculateLimits();
	broadcast(LOWER);
      }
      break;
    }
    case UPPER : {
      double oUpper = upper;
      link.access(JRealData(upper));
      if (oUpper != upper) {
        calculateLimits();
	broadcast(UPPER);
      }
      break;
    }
    case IN_LAST : { // Decalibrate FeedBack
      int oFeedback = feedback;
      link.access(JIntegerData(feedback));
      if (oFeedback != feedback) {
	decalibrate = (double(feedback)*(upperLimit-lowerLimit)/mask)+lowerLimit;
        broadcast(CALIBRATE);
      }
      break;
    }
  }
}

JArray JRCalibrateObj::getProperties() {
  JArray properties = JANDObj::getProperties();
  properties.append(JIntegerProperty("fraction", fraction, 0, 98));
  properties.append(JRealProperty("lower", lower));
  properties.append(JRealProperty("upper", upper));
  return properties;
}

boolean JRCalibrateObj::updateProperty(JProperty& prop) {
  if (JANDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("fraction")) {
    fraction = ((JIntegerProperty*)&prop)->value;
    calculateLimits();
    return true;
  } else if (prop.getName() == JString("lower")) {
    lower = ((JRealProperty*)&prop)->value;
    calculateLimits();
    broadcast(LOWER);
    return true;
  } else if (prop.getName() == JString("upper")) {
    upper = ((JRealProperty*)&prop)->value;
    calculateLimits();
    broadcast(UPPER);
    return true;
  }
  return false;
}

