#include "JDateData.h"

const int JDateData::id = 9;
const JColor JDateData::color = JColor(255, 128, 128).darker();
const char* JDateData::className() const { return "JDateData";}
const char* JDateData::sid() const { return "D";}
JObject* JDateData::clone() const { return new JDateData(*this);}
int JDateData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return value.compareTo((*(JDateData*)&s).value);
}

JDateData::JDateData(JDate& _value) : value(_value) {}
JDateData::operator JDate&() const { return value;}
void JDateData::reset() const { value = JDate();}
void JDateData::assign(const JObject& obj) const
{ value = *(JDate*)&obj;}
