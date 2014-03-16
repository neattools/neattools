#include "JRealData.h"
#include "JDouble.h"
#include "JMath.h"

const int JRealData::id = 2;
const JColor JRealData::color = JColor::green.darker();
const char* JRealData::className() const { return "JRealData";}
const char* JRealData::sid() const { return "R";}
JObject* JRealData::clone() const { return new JRealData(*this);}

int JRealData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return cmp(value, (*(JRealData*)&s).value);
}

JRealData::JRealData(double& _value) : value(_value) {}
JRealData::operator double&() const { return value;}
void JRealData::reset() const { value = 0.0;}
void JRealData::assign(const JObject& obj) const
{ value = (double)*(JDouble*)&obj;}
