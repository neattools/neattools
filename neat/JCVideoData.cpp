#include "JCVideoData.h"
#include "JMath.h"

const int JCVideoData::id = 11;
const char* JCVideoData::className() const { return "JCVideoData";}
const char* JCVideoData::sid() const { return "v";}
JObject* JCVideoData::clone() const { return new JCVideoData(*this);}
JCVideoData::JCVideoData(JBlock& _value) : JBlockData(_value) {}
