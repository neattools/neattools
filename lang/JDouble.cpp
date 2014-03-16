#include "JDouble.h"
#include "JBlock.h"
#include "JMath.h"
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

double JDouble::MIN_VALUE = DBL_MIN;
double JDouble::MAX_VALUE = DBL_MAX;
double JDouble::EPSILON = DBL_EPSILON;
char* theJDouble = JDouble().Register();

void JDouble::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putDouble(os, "value", value);
}

void JDouble::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = getDouble(dict, "value");
}

JString JDouble::toJString(double r) { 
  JBlock buf(50, 0);
  sprintf(buf, "%lf", r);
  return JString(buf);
}

JString JDouble::toJStringF(double r, int w, int f) { 
  if (w <= 0) return toJString(r);
  JBlock buf(50, 0), format(50, 0);
  sprintf(format, "%%%d.%dlf", w, f);
  sprintf(buf, format, r);
  return JString(buf);
}

double JDouble::parse(JString s) { 
  double v = 0.0;
  sscanf(s, "%lf", &v);
  return v;
}

const char* JDouble::className() const { return "JDouble";}

int JDouble::hashCode() const
{ return hashMask & (int)value;}
JObject* JDouble::clone() const { return new JDouble(*this);}

int JDouble::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return cmp(value, ((JDouble*)&s)->value);
}

JDouble::JDouble() : value(0.0) {}
JDouble::JDouble(double _value) : value(_value) {}
JDouble::JDouble(JString s) 
  : value(parse(s)) {}

JDouble::operator double&() { return value;}
JString JDouble::toJString() { return toJString(value);}

