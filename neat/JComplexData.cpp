#include "JComplexData.h"
#include "JComplex.h"
#include "JMath.h"

const int JComplexData::id = 12;
const JColor JComplexData::color = JColor(128, 128, 128).darker();
const char* JComplexData::className() const { return "JComplexData";}
const char* JComplexData::sid() const { return "c";}
JObject* JComplexData::clone() const { return new JComplexData(*this);}
int JComplexData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return cmp(value.norm(), ((JComplexData*)&s)->value.norm());
}

JComplexData::JComplexData(jcomplex& _value) : value(_value) {}
JComplexData::operator jcomplex&() const { return value;}
void JComplexData::reset() const { value = jcomplex();}
void JComplexData::assign(const JObject& obj) const
{ value = *(JComplex*)&obj;}
