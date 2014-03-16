#include "JObjectPtr.h"

char* theJObjectPtr = JObjectPtr().Register();
const char* JObjectPtr::className() const { return "JObjectPtr";}
int JObjectPtr::hashCode() const
{ return hashMask & (obj ? obj->hashCode() : null);}
JObject* JObjectPtr::clone() const { return new JObjectPtr(*this);}

void JObjectPtr::forEach(iterFuncType func, void** arg) const
{ (*func)(obj, arg);}

JObject* JObjectPtr::firstThat(condFuncType func, void** arg) const
{ return (*func)(obj, arg) ? obj : null;}

JObject* JObjectPtr::lastThat(condFuncType func, void** arg) const
{ return (*func)(obj, arg) ? obj : null;}

int JObjectPtr::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return obj-((JObjectPtr*)&s)->obj;
}

JObjectPtr::JObjectPtr(const JObject* _obj) : JPObject(_obj) {}
