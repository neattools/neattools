#include "JStringData.h"
#include "JMath.h"

const int JStringData::id = 3;
const JColor JStringData::color = JColor::yellow.darker();
const char* JStringData::className() const { return "JStringData";}
const char* JStringData::sid() const { return "S";}
JObject* JStringData::clone() const { return new JStringData(*this);}

int JStringData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return cmp(value, (*(JStringData*)&s).value);
}

JStringData::JStringData(JString& _value) : value(_value) {}
JStringData::operator JString&() const { return value;}
void JStringData::reset() const { value = JString();}
void JStringData::assign(const JObject& obj) const
{ value = *(JString*)&obj;}
