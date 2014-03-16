#include "JIntegerData.h"
#include "JInteger.h"
#include "JMath.h"

const int JIntegerData::id = 1;
const char* JIntegerData::className() const { return "JIntegerData";}
const char* JIntegerData::sid() const { return "I";}
JObject* JIntegerData::clone() const { return new JIntegerData(*this);}

int JIntegerData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return cmp(value, (*(JIntegerData*)&s).value);
}

JIntegerData::JIntegerData(int& _value) : value(_value) {}
JIntegerData::operator int&() const { return value;}
void JIntegerData::reset() const { value = 0;}
void JIntegerData::assign(const JObject& obj) const
{ value = (int)*(JInteger*)&obj;}
