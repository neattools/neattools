#include "JVideoData.h"
#include "JMath.h"

const int JVideoData::id = 7;
const char* JVideoData::className() const { return "JVideoData";}
const char* JVideoData::sid() const { return "V";}
JObject* JVideoData::clone() const { return new JVideoData(*this);}
JVideoData::JVideoData(JBlock& _value) : JBlockData(_value) {}
