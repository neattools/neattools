#include "JColorData.h"
#include "JMath.h"

const int JColorData::id = 4;
const char* JColorData::className() const { return "JColorData";}
const char* JColorData::sid() const { return "C";}
JObject* JColorData::clone() const { return new JColorData(*this);}

int JColorData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return cmp(value, (*(JColorData*)&s).value);
}

JColorData::JColorData(JColor& _value) : value(_value) {}
JColorData::operator JColor&() const { return value;}
void JColorData::reset() const { value = JColor();}
void JColorData::assign(const JObject& obj) const
{ value = *(JColor*)&obj;}


