#include "JDictionary.h"
#include "JAssociation.h"
#include "JString.h"

char* theJDictionary = JDictionary().Register();
const char* JDictionary::className() const { return "JDictionary";}
JObject* JDictionary::clone() const { return new JDictionary(*this);}

JDictionary::JDictionary() {}
JDictionary::JDictionary(int sz) : JHashTable(sz) {}

JObject* JDictionary::operator[](const JObject& key) {
  JObject *assoc = JHashTable::operator[](JAssociation(key));
  return (assoc) ? ((JAssociation*)assoc)->value() : null;
}

JObject* JDictionary::add(const JObject& key) 
{ return JHashTable::add(JAssociation(key));}

JObject* JDictionary::add(const JObject& key, const JObject& val) 
{ return JHashTable::add(JAssociation(key, val));}

JObject* JDictionary::del(const JObject& key) 
{ return JHashTable::del(JAssociation(key));}
