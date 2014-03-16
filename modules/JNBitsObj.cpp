#include "JNBitsObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJNBitsObj = JNBitsObj().Register();
void JNBitsObj::writeContent(JOutputStream& os) {
  JLEDObj::writeContent(os);
  putInteger(os, "NB", NB);
}

void JNBitsObj::readContent(JDictionary& dict) {
  JLEDObj::readContent(dict);
  updateNB(NB = getInteger(dict, "NB"));
}

const char* JNBitsObj::className() const { return "JNBitsObj";}
JObject* JNBitsObj::clone() const { return new JNBitsObj(*this);}
JNBitsObj::JNBitsObj() { NB = 16; mask = 0xFFFF;}

JString JNBitsObj::inputTag(int n) {
  char* tag[] = { "input", "color", "background"};
  if (!n) return JString(tag[n])+NBTag();
  return tag[n];
}

JString JNBitsObj::outputTag(int n) 
{ return JString("output")+NBTag();}

JArray JNBitsObj::getProperties() {
  JArray properties = JLEDObj::getProperties();
  properties.append(JIntegerProperty("N bit(s)", NB, 1, 32));
  return properties;
}

boolean JNBitsObj::updateProperty(JProperty& prop) {
  if (JLEDObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("N bit(s)")) {
    if (updateNB(((JIntegerProperty*)&prop)->value)) 
      broadcast(0);
    return true;
  }
  return false;
}

boolean JNBitsObj::updateNB(int _NB) {
  if (!_NB) _NB = 16;
  _NB = max(1, min(32, _NB));
  mask = 0xFFFFFFFF >> (32-_NB);
  if (NB != _NB) {
    value = matchBack(value, _NB);
    NB = _NB;
    return true;
  }
  return false;
}

JString JNBitsObj::NBTag() { 
  if (NB == 1) return JString("(")+JInteger::toJString(NB)+"bit)";
  return JString("(")+JInteger::toJString(NB)+"bits)";
}

int JNBitsObj::matchNB(int v, int nb) {
  if (NB > nb) v <<= (NB-nb);
  else if (NB < nb) v >>= (nb-NB);
  return v;
}

int JNBitsObj::matchBack(int v, int nb) {
  if (NB > nb) v >>= (NB-nb);
  else if (NB < nb) v <<= (nb-NB);
  return v;
}
