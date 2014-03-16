#include "JHashTable.h"
#include "JList.h"

char* theJHashTable = JHashTable().Register();
void JHashTable::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putObject(os, "entry", entry);
}

void JHashTable::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  entry = *(JArray*)getObject(dict, "entry");
}

const char* JHashTable::className() const { return "JHashTable";}
JObject* JHashTable::clone() const { return new JHashTable(*this);}
void JHashTable::forEach(iterFuncType func, void** arg) const
{ entry.forEach(func, arg);}

JObject* JHashTable::firstThat(condFuncType func, void** arg) const
{ return entry.firstThat(func, arg);}

int JHashTable::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return entry.compareTo(((JHashTable*)&s)->entry);
}

JHashTable::JHashTable() {}
JHashTable::JHashTable(int sz) : entry(sz) {}

JObject* JHashTable::operator[](const JObject& obj) {
  int hash = obj.hashCode() % size();
  if (!entry[hash]) return null;
  return ((*(JList*)entry[hash])[obj]);
}

JObject* JHashTable::add(const JObject& obj) {
  int hash = obj.hashCode() % size();
  if (!entry[hash]) entry.set(hash, JList());
  return (*(JList*)entry[hash]).add(obj);
}

JObject* JHashTable::del(const JObject& obj) {
  int hash = obj.hashCode() % size();
  return (*(JList*)entry[hash]).del(obj);
}

void DoRehash(const JObject* obj, void** arg) 
{ (*(JHashTable*)arg).add(*obj);}

void JHashTable::rehash(int sz) {
  if (entry.size() == sz) return;
  JHashTable dest(sz);
  forEach(DoRehash, (void**)&dest);
  *this = dest;
}

#if defined(BC5)
void DoCount(const JObject*, void** arg) { (*(int*)arg)++;}
#else
void DoCount(const JObject* obj, void** arg) { (*(int*)arg)++;}
#endif

int JHashTable::size() const { return entry.size();}
int JHashTable::count() const {
  int ct = 0;
  forEach(DoCount, (void**)&ct);
  return ct;
}

void JHashTable::Dereference() { entry.Dereference();}

void JHashTable::Release() { entry.Release();}
