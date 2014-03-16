#include "JPObject.h"

char* theJPObject = JPObject().Register();
void JPObject::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "obj", (int)obj);
}

void JPObject::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  obj = (JObject*)getInteger(dict, "obj");
}

const char* JPObject::className() const { return "JPObject";}
int JPObject::hashCode() const { return hashMask & (int)obj;}
JObject* JPObject::clone() const { return new JPObject(*this);}

int JPObject::compareTo(const JObject& s) const {
  if (className() != s.className()) return false;
  return obj-((JPObject*)&s)->obj;
}

JPObject::JPObject(const JObject* _obj) { obj = (JObject*)_obj;}
JPObject::operator JObject*() const { return obj;}
