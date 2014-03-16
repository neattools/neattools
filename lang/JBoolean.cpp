#include "JBoolean.h"
#include <limits.h>

boolean JBoolean::MIN_VALUE = 0;
boolean JBoolean::MAX_VALUE = UCHAR_MAX;
JBoolean JBoolean::TRUE(true);
JBoolean JBoolean::FALSE(false);
char* theJBoolean = JBoolean().Register();

void JBoolean::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "value", toJString(value));
}

void JBoolean::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = (boolean)JBoolean(getString(dict, "value"));
}

JString JBoolean::toJString(boolean b) 
{ return JString((b)?"true":"false");}

boolean JBoolean::parse(JString s) 
{ return s == "true";}

const char* JBoolean::className() const { return "JBoolean";}

int JBoolean::hashCode() const
{ return hashMask & (int)value;}
JObject* JBoolean::clone() const { return new JBoolean(*this);}

int JBoolean::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return value-((JBoolean*)&s)->value;
}

JBoolean::JBoolean() : value(0) {}
JBoolean::JBoolean(boolean _value) : value(_value) {}
JBoolean::JBoolean(JString s) 
  : value(parse(s)) {}

JBoolean::operator boolean&() { return value;}
JString JBoolean::toJString() { return toJString(value);}

