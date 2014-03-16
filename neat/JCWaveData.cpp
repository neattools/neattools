#include "JCWaveData.h"
#include "JMath.h"

const int JCWaveData::id = 10;
const char* JCWaveData::className() const { return "JCWaveData";}
const char* JCWaveData::sid() const { return "w";}
JObject* JCWaveData::clone() const { return new JCWaveData(*this);}
JCWaveData::JCWaveData(JBlock& _value) : JBlockData(_value) {}
