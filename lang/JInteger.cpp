#include "JInteger.h"
#include "JCharacter.h"
#include <limits.h>

int JInteger::MIN_VALUE = INT_MIN;
int JInteger::MAX_VALUE = INT_MAX;
char* theJInteger = JInteger().Register();

void JInteger::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "value", value);
}

void JInteger::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getInteger(dict, "value");
}

JString JInteger::toJString(int i, int radix)
{ return JCharacter::toJString(i, radix);}

int JInteger::parse(JString s, int radix)
{ return JCharacter::parse(s, radix);}

const char* JInteger::className() const { return "JInteger";}

int JInteger::hashCode() const
{ return hashMask & value;}
JObject* JInteger::clone() const { return new JInteger(*this);}

int JInteger::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return value-((JInteger*)&s)->value;
}

JInteger::JInteger() : value(0) {}
JInteger::JInteger(int _value) : value(_value) {}
JInteger::JInteger(JString s, int radix) 
  : value(parse(s, radix)) {}

JInteger::operator int&() { return value;}
JString JInteger::toJString() { return toJString(value);}


