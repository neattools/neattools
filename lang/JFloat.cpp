#include "JFloat.h"
#include "JBlock.h"
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

float JFloat::MIN_VALUE = FLT_MIN;
float JFloat::MAX_VALUE = FLT_MAX;
float JFloat::EPSILON = FLT_EPSILON;

char* theJFloat = JFloat().Register();
void JFloat::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putFloat(os, "value", value);
}

void JFloat::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getFloat(dict, "value");
}

JString JFloat::toJString(float r) { 
  JBlock buf(50, 0);
  sprintf(buf, "%f", r);
  return JString(buf);
}

float JFloat::parse(JString s) {
  float f = 0;
  sscanf(s, "%f", &f);
  return f;
}

const char* JFloat::className() const { return "JFloat";}

int JFloat::hashCode() const
{ return hashMask & (int)value;}
JObject* JFloat::clone() const { return new JFloat(*this);}

int JFloat::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  float d = (value-((JFloat*)&s)->value);
  if (d==0.0F) return 0;
  if (d>0.0F) return 1;
  return -1;
}

JFloat::JFloat() : value(0.0F) {}
JFloat::JFloat(float _value) : value(_value) {}
JFloat::JFloat(JString s) 
  : value(parse(s)) {}

JFloat::operator float&() { return value;}
JString JFloat::toJString() { return toJString(value);}

