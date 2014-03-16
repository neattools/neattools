#include "JProperty.h"

void JProperty::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "name", name);
  putInteger(os, "dirty", dirty);
}

void JProperty::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  name = getString(dict, "name");
  dirty = (boolean)getInteger(dict, "dirty");
}

const char* JProperty::className() const { return "JProperty";}

int JProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return name.compareTo(((JProperty*)&s)->name);
}

JProperty::JProperty() { dirty = false;}
JProperty::JProperty(JString _name) : name(_name) { dirty = false;}
JString JProperty::getName() { return name;}
boolean JProperty::isDirty() { return dirty;}
boolean JProperty::check() { return true;}

