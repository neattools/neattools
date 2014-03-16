#include "JMIDIData.h"
#include "JMath.h"

const int JMIDIData::id = 5;
const char* JMIDIData::className() const { return "JMIDIData";}
const char* JMIDIData::sid() const { return "M";}
JObject* JMIDIData::clone() const { return new JMIDIData(*this);}
JMIDIData::JMIDIData(int& _value) : JIntegerData(_value) {}
