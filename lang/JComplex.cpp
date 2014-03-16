#include "JBlock.h"
#include "JMath.h"
#include <stdlib.h>
#include <stdio.h>
#include "JComplex.h"
#include "JDouble.h"

char* theJComplex = JComplex().Register();

void JComplex::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putDouble(os, "real", value.r);
  putDouble(os, "imag", value.i);
}

void JComplex::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value.r = getDouble(dict, "real");
  value.i = getDouble(dict, "image");
}

JString JComplex::toJString(const jcomplex& c) { 
  JBlock buf(50, 0);
  sprintf(buf, "%.10lg,%.10lgi", c.r, c.i);
  return JString(buf);
}

JString JComplex::toJStringF(const jcomplex& c, int w, int f) { 
  if (w <= 0) return toJString(c);
  JBlock buf(50, 0), format(50, 0);
  sprintf(format, "%%%d.%dlf,%%%d.%dlfi", w, f, w, f);
  sprintf(buf, format, c.r, c.i);
  return JString(buf);
}

JString JComplex::toJStringH(const jcomplex& c) { 
  JBlock buf(50, 0);
  sprintf(buf, "%.20lg,%.20lgi", c.r, c.i);
  return JString(buf);
}

jcomplex JComplex::parse(JString s) {
  jcomplex c;
  int p1 = s.indexOf(',');
  if (p1 == -1) {
    c.r = JDouble::parse(s);
    return c;
  }
  c.r = JDouble::parse(s(0, p1));
  int p2 = s.indexOf('i');
  if (p2 == -1) return c;
  c.i = JDouble::parse(s(p1+1, p2));
  return c;
}

const char* JComplex::className() const { return "JComplex";}

int JComplex::hashCode() const
{ return hashMask & (int)(value.r+value.i);}
JObject* JComplex::clone() const { return new JComplex(*this);}

int JComplex::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return cmp(value.norm(), ((JComplex*)&s)->value.norm());
}

JComplex::JComplex() {}
JComplex::JComplex(const jcomplex& _value) : value(_value) {}
JComplex::JComplex(JString s) : value(parse(s)) {}

JComplex::operator jcomplex&() { return value;}
JString JComplex::toJString() { return toJString(value);}

