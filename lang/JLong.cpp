#include "JLong.h"
#include "JCharacter.h"
#include <limits.h>

long JLong::MIN_VALUE = LONG_MIN;
long JLong::MAX_VALUE = LONG_MAX;

char* theJLong = JLong().Register();
void JLong::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putLong(os, "value", value);
}

void JLong::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getLong(dict, "value");
}

JString JLong::toJString(long i, int radix) 
{ return JCharacter::toJString(i, radix);}

long JLong::parse(JString s, int radix) 
{ return JCharacter::parse(s, radix);}

const char* JLong::className() const { return "JLong";}

int JLong::hashCode() const
{ return hashMask & (int)value;}
JObject* JLong::clone() const { return new JLong(*this);}

int JLong::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return value-((JLong*)&s)->value;
}

JLong::JLong() : value(0) {}
JLong::JLong(long _value) : value(_value) {}
JLong::JLong(JString s, int radix) 
  : value(parse(s, radix)) {}

JLong::operator long&() { return value;}
JString JLong::toJString() { return toJString(value);}

