#include "JObject.h"
#include "JBlock.h"
#include "JDictionary.h"
#include "JInteger.h"
#include "JLong.h"
#include "JDouble.h"
#include "JFloat.h"
#include "JClassReferenceException.h"
#include "JIllegalArgumentException.h"
#include <limits.h>

#define MAXCLASSNAME 80

char nil = '\0';
char parenleft = '(';
JString parenright(")");
JString endline("\r\n");
JString tagValue("v");
JString tagObject("o");

char* theJObject = JObject().Register();
int JObject::hashMask = INT_MAX;
DllExport JDictionary *pClassDict = null;
DllExport JArray *pClassArray = null;

char* JObject::Register() {
  static JDictionary classDict(203);
  static JArray classArray;
  if (!pClassDict) {
    pClassDict = &classDict;
    pClassArray = &classArray;
  }
  pClassArray->append(JString(className()));
  pClassDict->add(JString(className()).toUpperCase(), *this);
  return (char*)className();
}

void JObject::write(JOutputStream& os) {
  os << endline << JString(className()) << parenleft;
  writeContent(os);
  os << parenright;
}

void JObject::writeContent(JOutputStream& os) 
{ putInteger(os, "prevAddress", (int)this);}

void JObject::putObject(class JOutputStream& os, char* key, JObject& obj) { 
  os << JString(key) << tagObject;
  obj.write(os);
}

JObject* JObject::getObject(JDictionary& dict, char* key) 
{ return dict[JString(key)];}

void JObject::putLong(class JOutputStream& os, char* key, long value)
{ putString(os, key, JLong::toJString(value, 16));}

long JObject::getLong(class JDictionary& dict, char* key, long value) { 
  JString *val = (JString*)dict[JString(key)];
  return (val) ? (long)JLong(*val, 16) : value;
}

void JObject::putInteger(class JOutputStream& os, char* key, int value) 
{ putString(os, key, JInteger::toJString(value, 16));}

int JObject::getInteger(class JDictionary& dict, char* key, int value) { 
  JString *val = (JString*)dict[JString(key)];
  return (val) ? (int)JInteger(*val, 16) : value;
}

void JObject::putFloat(class JOutputStream& os, char* key, float value)
{ putString(os, key, JFloat::toJString(value));}

float JObject::getFloat(class JDictionary& dict, char* key, float value) { 
  JString *val = (JString*)dict[JString(key)];
  return (val) ? (float)JFloat(*val) : value;
}

void JObject::putDouble(class JOutputStream& os, char* key, double value) 
{ putString(os, key, JDouble::toJString(value));}

double JObject::getDouble(class JDictionary& dict, char* key, double value) { 
  JString *val = (JString*)dict[JString(key)];
  return (val) ? (double)JDouble(*val) : value;
}

void JObject::putString(class JOutputStream& os, char* key, char* value) 
{ os << JString(key) << tagValue << JString(value);}

JString JObject::getString(class JDictionary& dict, char* key, char* value) {
  JString *val = (JString*)dict[JString(key)];
  return JString((val) ? (char*)*val : value, JString::needCopy);
}

void JObject::readContent(JDictionary& dict) 
{ prevAddress = (JObject*)getInteger(dict, "prevAddress");}

JObject* JObject::read(JInputStream& is) {
  JString prefix, name;
  JDictionary dict(101);
  char start;
  is >> prefix;
  is >> name;
  is >> start;
  if (start == parenleft) {
    JString id, val, type;
    for (;;) {
      is >> id;
      if (id[0] == parenright[0]) break;
      if (!id[0]) throw new JIllegalArgumentException();
      is >> type;
      switch (type[0]) {
        case 'v': {
          is >> val;
          dict.add(id, val);
          break;
        }
        case 'o': {
          JObject *o = read(is);
          dict.add(id, *o);
          delete o;
          break;
        }
        default:
          throw new JIllegalArgumentException();
      }
    }
  } else throw new JIllegalArgumentException();
  if (!name[0]) throw new JIllegalArgumentException();
  if (name != JString(className())) {
    JObject *obj = (*pClassDict)[JString(name).toUpperCase()];
    if (obj) {
      obj = DupPObj(obj);
      obj->readContent(dict);
    } else throw new JClassReferenceException(name);
    return obj;
  } else {
    readContent(dict);
    return this;
  }
}

JObject::JObject() { prevAddress = null;}
JObject::~JObject() {}
const char* JObject::className() const { return "JObject";}
int JObject::hashCode() const
{ return hashMask & (int)this;}
JObject* JObject::clone() const { return new JObject(*this);}
boolean JObject::isWindow() const { return false;}

void JObject::forEach(iterFuncType func, void** arg) const
{ (*func)(this, arg);}

JObject* JObject::firstThat(condFuncType func, void** arg) const
{ return (*func)(this, arg) ? (JObject*)this : null;}

JObject* JObject::lastThat(condFuncType func, void** arg) const
{ return (*func)(this, arg) ? (JObject*)this : null;}

int JObject::compareTo(const JObject& s) const {
  return this-&s;
}

void JObject::run() {}
boolean JObject::operator==(const JObject& s) const { return compareTo(s) == 0;}
boolean JObject::operator!=(const JObject& s) const { return compareTo(s) != 0;}
boolean JObject::operator>=(const JObject& s) const { return compareTo(s) >= 0;}
boolean JObject::operator<=(const JObject& s) const { return compareTo(s) <= 0;}
boolean JObject::operator> (const JObject& s) const { return compareTo(s) >  0;}
boolean JObject::operator< (const JObject& s) const { return compareTo(s) <  0;}

#if !defined(WIN32)
#include <stdio.h>
/*
void terminate() {
  perror("Unexpect Exception Exit!\n");
  exit(1);
}
*/
#endif


