#include "JBytesData.h"
#include "JMath.h"

const int JBytesData::id = 8;
const JColor JBytesData::color = JColor(192, 192, 255).darker();
const char* JBytesData::className() const { return "JBytesData";}
const char* JBytesData::sid() const { return "B";}
JObject* JBytesData::clone() const { return new JBytesData(*this);}
JBytesData::JBytesData(JBlock& _value) : JBlockData(_value) {}
