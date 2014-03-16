#include "JAssociation.h"

char* theJAssociation = JAssociation().Register();
void JAssociation::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  if (aKey) putObject(os, "aKey", *aKey);
  if (aValue) putObject(os, "aValue", *aValue);
}

void JAssociation::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  JObject *nKey = getObject(dict, "aKey");
  JObject *nValue = getObject(dict, "aValue");
  SetPObj(aKey, nKey);
  SetPObj(aValue, nValue);
}

const char* JAssociation::className() const { return "JAssociate";}
int JAssociation::hashCode() const { return aKey->hashCode();}
JObject* JAssociation::clone() const { return new JAssociation(*this);}
int JAssociation::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return aKey->compareTo(*(((JAssociation*)&s)->aKey));
}

JAssociation::JAssociation():aKey(null), aValue(null) {}
JAssociation::JAssociation(const JObject& k)
  :aKey(DupPObj(&k)), aValue(null) {}
JAssociation::JAssociation(const JObject& k, const JObject& v)
  :aKey(DupPObj(&k)), aValue(DupPObj(&v)) {}
JAssociation::JAssociation(const JAssociation& a)
  :aKey(null), aValue(null) {
  *this=a;
}

JAssociation::~JAssociation() {
  DelPObj(aKey);
  DelPObj(aValue);
}

JAssociation& JAssociation::operator=(const JAssociation& a) {
  SetPObj(aKey, a.aKey);
  SetPObj(aValue, a.aValue);
  return *this;
}

JObject* JAssociation::key() const { return aKey;}
JObject* JAssociation::value() const { return (aValue) ? aValue : aKey;}
JObject* JAssociation::setKey(const JObject& k) { return SetPObj(aKey, &k);}
JObject* JAssociation::setValue(const JObject& v) { return SetPObj(aValue, &v);}
