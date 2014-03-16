#include "JBlockData.h"
#include "JMath.h"

const int JBlockData::id = 0;
const char* JBlockData::className() const { return "JBlockData";}
const char* JBlockData::sid() const { return "K";}
JObject* JBlockData::clone() const { return new JBlockData(*this);}

int JBlockData::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return value.compareTo((*(JBlockData*)&s).value);
}

JBlockData::JBlockData(JBlock& _value) : value(_value) {}
JBlockData::operator JBlock&() const { return value;}
void JBlockData::reset() const { value = JBlock();}
void JBlockData::assign(const JObject& obj) const 
{ value = *(JBlock*)&obj;}
