#include "JDateObj.h"
#include "JDateData.h"
#include "JString.h"
#include "JColorData.h"
#include "JStringData.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JLinkObj.h"
#include <stdio.h>

char* theJDateObj = JDateObj().Register();
void JDateObj::writeContent(JOutputStream& os) {
  JLabelObj::writeContent(os);
  putDouble(os, "rvalue", (double)date);
  putInteger(os, "mode", mode);
}

void JDateObj::readContent(JDictionary& dict) {
  JLabelObj::readContent(dict);
  date = JDate(getDouble(dict, "rvalue"));
  mode = getInteger(dict, "mode");
  updateValue();
  label = getText();
}

const char* JDateObj::className() const { return "JDateObj";}
JObject* JDateObj::clone() const { return new JDateObj(*this);}

JDateObj::JDateObj() {
  color = JColor::red;
  bkgnd = JColor::black;
  igm = IN_LAST;
  ogm = OUT_LAST;
  mode = DATE_MASK;
  updateValue();
  label = getText();
  for (int i=0; i<OUT_NEXTFOCUS; i++)
    ov[i] = -1;
}

JString JDateObj::getText() {
  char buf[35];
  JString data;
  if (mode & DATE_MASK) {
    sprintf(buf, "%02d/%02d", v[MONTH]+1, v[DATE]);
    data += buf;
    if (mode & YEAR_MASK) {
      sprintf(buf, "/%04d", v[YEAR]);
      data += buf;
    }
  }
  if (mode & TIME_MASK) {
    if (mode & DATE_MASK) data += " ";
    sprintf(buf, "%02d:%02d", v[HOURS], v[MINUTES]);
    data += buf;
    if (mode & SECONDS_MASK) {
      sprintf(buf, ":%02d", v[SECONDS]);
      data += buf;
      if (mode & MILLIS_MASK) {
        sprintf(buf, ".%03d", v[MILLIS]);
        data += buf;
      }

    }
  }
  if ((mode & WEEK_MASK) && (mode & DATE_MASK))
    data += JString(" ")+JString(JDate::weekTag[v[WDAY]])(0, 3);
  return data;
}

int JDateObj::inputType(int n) { 
  switch (n) {
    case DATA: return JDateData::id;
    case IN_COLOR:
    case IN_BKGND: return JColorData::id;
    case IN_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

int JDateObj::outputType(int n) { 
  switch (n) {
    case DATA : return JDateData::id;
    case WEEK_TAG :
    case MONTH_TAG : 
    case OUT_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

void JDateObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case DATA : 
      data.assign(date);
      break;
    case WEEK_TAG : 
      JSTRING(data) = JDate::weekTag[date.getWDay()]; 
      break;
    case MONTH_TAG : 
      JSTRING(data) = JDate::monthTag[date.getMonth()]; 
      break;
    case OUT_STRING :
      JSTRING(data) = label;
      break;
    case OUT_NEXTFOCUS:
      INT(data) = nextFocus;
      break;
    case OUT_ENTER:
      INT(data) = enterPressed;
      break;
    case OUT_ESCAPE:
      INT(data) = escapePressed;
      break;
    default:
      INT(data) = v[n];
  }
}

boolean JDateObj::inputAllowed(int n) {
  if (!n) {
    return !inputSet(n).last() &&
      !inputSet(MILLIS).last() &&
      !inputSet(SECONDS).last() &&
      !inputSet(MINUTES).last() &&
      !inputSet(HOURS).last() &&
      !inputSet(DATE).last() &&
      !inputSet(MONTH).last() &&
      !inputSet(YEAR).last();
  } else {
    if (n < IN_COLOR) {
      return !inputSet(n).last() &&
        !inputSet(0).last();
    }
    return !inputSet(n).last();
  }
}

JString JDateObj::inputTag(int n) { 
  char* tag[] = {
    "data-in", "millis-in(0-999)", "seconds-in(0-59)", "minutes-in(0-59)", "hours-in(0-23)",
    "date-in(1-31)", "month-in(0-11)", "year-in(1900-)", 
    "color", "background", "editFocus(logical)",
    "string-in"};
  return tag[n];
}

JString JDateObj::outputTag(int n) { 
  char* tag[] = {
    "data-out", "millis-out(0-999)", "seconds-out(0-59)", "minutes-out(0-59)", "hours-out(0-23)",
    "date-out(1-31)", "month-out(0-11)", "year-out(1900-)", "wday-out(0-6)", 
    "yday-out(0-365)", "dst-out(0-1)", "weekTag-out", "monthTag-out",
    "nextFocus(logical)", "enterKey(logical)", "escapeKey(logical)",
    "string-out"};
  return tag[n];
}

JFRect JDateObj::inputArea(int n) { 
  if (n < IN_COLOR) return leftArea(n, 0, IN_COLOR, 0, 1);
  return topArea(n, IN_COLOR, IN_LAST-IN_COLOR);
}

JFRect JDateObj::outputArea(int n) { 
  if (n < OUT_NEXTFOCUS) return rightArea(n, 0, OUT_NEXTFOCUS, 0, 1);
  return bottomArea(n, OUT_NEXTFOCUS, OUT_LAST-OUT_NEXTFOCUS);
}

int JDateObj::inputFace(int n)
{ return (n < IN_COLOR) ? LEFT : TOP;}

int JDateObj::outputFace(int n) 
{ return (n < OUT_NEXTFOCUS) ? RIGHT : BOTTOM;}

JFPoint JDateObj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_COLOR) return leftPoint(n, link, 0, IN_COLOR, 0, 1);
  return topPoint(n, link, IN_COLOR, IN_LAST-IN_COLOR);
}

JFPoint JDateObj::outputPoint(int n, JLinkObj& link) { 
  if (n < OUT_NEXTFOCUS) return rightPoint(n, link, 0, OUT_NEXTFOCUS, 0, 1);
  return bottomPoint(n, link, OUT_NEXTFOCUS, OUT_LAST-OUT_NEXTFOCUS);
}

void JDateObj::engine(int n, JLinkObj& link) {
  if (n == DATA) {
    JDate _date = date;
    link.access(JDateData(_date));
    setDValue(_date);
  } else if (n < IN_COLOR) {
    int oldv = v[n];
    link.access(JIntegerData(v[n]));
    if (oldv == v[n]) return;
    setDValue(JDate(v[YEAR], v[MONTH], v[DATE],
      v[HOURS], v[MINUTES], v[SECONDS], v[MILLIS]));
  } else if (n == IN_STRING) {
	JString iv = JDate::toJString((double)date);
    link.access(JStringData(iv));
    setDValue(JDate(iv));
  } else JLabelObj::engine(n-IN_COLOR+1, link);
}

JArray JDateObj::getProperties() {
  JArray properties = JLabelObj::getProperties();
  properties.append(JIntegerListProperty("show date", (mode & DATE_MASK) != 0, 
    JIntegerListProperty::booleanTag));
  if (mode & DATE_MASK) {
    properties.append(JIntegerListProperty("show year", (mode & YEAR_MASK) != 0, 
      JIntegerListProperty::booleanTag));
    properties.append(JIntegerListProperty("show week", (mode & WEEK_MASK) != 0, 
      JIntegerListProperty::booleanTag));
  }
  properties.append(JIntegerListProperty("show time", (mode & TIME_MASK) != 0, 
    JIntegerListProperty::booleanTag));
  if (mode & TIME_MASK) {
    properties.append(JIntegerListProperty("show seconds", (mode & SECONDS_MASK) != 0, 
      JIntegerListProperty::booleanTag));
    properties.append(JIntegerListProperty("show millis", (mode & MILLIS_MASK) != 0, 
      JIntegerListProperty::booleanTag));
  }
  properties.append(JIntegerProperty("year", v[YEAR], 1900, 2230));
  properties.append(JIntegerListProperty("month", v[MONTH], JDate::monthTag));
  properties.append(JIntegerProperty("date", v[DATE], 1, 31));
  properties.append(JIntegerProperty("hours", v[HOURS], 0, 23));
  properties.append(JIntegerProperty("minutes", v[MINUTES], 0, 59));
  properties.append(JIntegerProperty("seconds", v[SECONDS], 0, 59));
  properties.append(JIntegerProperty("millis", v[MILLIS], 0, 999));
  return properties;
}

boolean JDateObj::updateProperty(JProperty& prop) {
  if (JLabelObj::updateProperty(prop)) return true;
  boolean changed = false;
  if (prop.getName() == JString("show date")) {
    changeMode(DATE_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("show year")) {
    changeMode(YEAR_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("show week")) {
    changeMode(WEEK_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("show time")) {
    changeMode(TIME_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("show seconds")) {
    changeMode(SECONDS_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("show millis")) {
    changeMode(MILLIS_MASK, ((JIntegerListProperty*)&prop)->value);
    setLabel(label);
  } else if (prop.getName() == JString("year")) {
    v[YEAR] = ((JIntegerProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("month")) {
    v[MONTH] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("date")) {
    v[DATE] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("hours")) {
    v[HOURS] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("minutes")) {
    v[MINUTES] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("seconds")) {
    v[SECONDS] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("millis")) {
    v[MILLIS] = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  }
  if (changed) 
    setDValue(JDate(v[YEAR], v[MONTH], v[DATE],
      v[HOURS], v[MINUTES], v[SECONDS], v[MILLIS]));
  return true;
}

void JDateObj::updateValue() {
  v[DATA] = (int)date;
  v[MILLIS] = date.getMillis();
  v[SECONDS] = date.getSeconds();
  v[MINUTES] = date.getMinutes();
  v[HOURS] = date.getHours();
  v[DATE] = date.getDate();
  v[MONTH] = date.getMonth();
  v[YEAR] = date.getYear();
  v[WDAY] = date.getWDay();
  v[YDAY] = date.getYDay();
  v[DST] = date.isDST();
  v[WEEK_TAG] = v[WDAY];
  v[MONTH_TAG] = v[MONTH];
}

boolean JDateObj::setDValue(JDate _date) {
  if (date != _date) {
    date = _date;
    updateValue();
    label = getText();
    for (int i=0; i<OUT_NEXTFOCUS; i++)
      if (ov[i] != v[i]) {
        ov[i] = v[i];
        broadcast(i);
      }
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JDateObj::setLabel(JString _label) {
  if (setDValue(JDate(_label))) return true;
  _label = getText();
  if (_label != label) {
    label = _label;
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

void JDateObj::changeMode(int mask, boolean status) {
  if (status) mode |= mask;
  else mode &= ~mask;
}

JString JDateObj::getEditSet() { return "/: 0123456789";}

void JDateObj::processCtrlKeys(int key) {
  switch (key) {
    case JEvent::JK_Return:
      enterPressed = true;
      broadcast(OUT_ENTER);
      setLabel(label);
      enterPressed = false;
      broadcast(OUT_ENTER);
      break;
    case JEvent::JK_Escape:
      escapePressed = true;
      broadcast(OUT_ESCAPE);
      setLabel(label);
      escapePressed = false;
      broadcast(OUT_ESCAPE);
      break;
    case JEvent::JK_Tab:
      nextFocus = true;
      broadcast(OUT_NEXTFOCUS);
      setLabel(label);
      nextFocus = false;
      broadcast(OUT_NEXTFOCUS);
      break;
  }
}

