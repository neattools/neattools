#include "JWaveData.h"
#include "JMath.h"

const int JWaveData::id = 6;
const char* JWaveData::className() const { return "JWaveData";}
const char* JWaveData::sid() const { return "W";}
JObject* JWaveData::clone() const { return new JWaveData(*this);}
JWaveData::JWaveData(JBlock& _value) : JBlockData(_value) {}
