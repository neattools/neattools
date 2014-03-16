#include "JDataBase.h"
#include "JBlock.h"
#include "JPObject.h"
#include "JInteger.h"
#include "JBlockOutputStream.h"
#include "JBlockInputStream.h"
#include "JIOException.h"
#include "JEOFException.h"
#include "JClassReferenceException.h"
#include "JIllegalArgumentException.h"

char* theJDataField = JDataField().Register();

void JDataField::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "name", name);
  putString(os, "type", type);
  putInteger(os, "id", id);
}

void JDataField::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  name = getString(dict, "name");
  type = getString(dict, "type");
  id = getInteger(dict, "id");
}

const char* JDataField::className() const { return "JDataField";}
JObject* JDataField::clone() const { return new JDataField(*this);}

int JDataField::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JDataField &a = *(JDataField*)&s;
  return name.compareTo(a.name);
}

JDataField::JDataField() { id = 0;}
JDataField::JDataField(JString _name, JString _type, int _id) {
  name = _name;
  type = _type;
  id = _id;
}

JString JDataField::getName() { return name;}
JString JDataField::getType() { return type;}
int JDataField::getId() { return id;}

int JDataBase::convertBase = 128;
char* theJDataBase = JDataBase().Register();

void JDataBase::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "header", header);
  putInteger(os, "numOfField", numOfField);
  putInteger(os, "currentId", currentId);
  putInteger(os, "sortId", sortId);
  putObject(os, "fields", fields);
}

void JDataBase::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  header = getString(dict, "header");
  numOfField = getInteger(dict, "numOfField");
  currentId = getInteger(dict, "currentId");
  sortId = getInteger(dict, "sortId");
  JObject *obj = getObject(dict, "fields");
  if (obj) fields = *(JArray*)obj;
}

const char* JDataBase::className() const { return "JDataBase";}
JObject* JDataBase::clone() const { return new JDataBase(*this);}

int JDataBase::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  JDataBase &a = *(JDataBase*)&s;
  return fa.compareTo(a.fa);
}

JDataBase::JDataBase() {
  numOfField = 0;
  currentId = 0;
  sortId = 0;
  valid = false;
}

JDataBase::JDataBase(JString fname, boolean _readOnly) 
{ open(fname, _readOnly);}

JDataBase::~JDataBase() { close();}

void JDataBase::open(JString fname, boolean _readOnly) {
  valid = false;
  fa.open(fname, _readOnly);
  if (fa.isEmpty()) {
    if (!_readOnly) {
      JBlock data;
      JBlockOutputStream bos(data);
      header = "NDBF";
      numOfField = 0;
      currentId = 0;
      sortId = 0;
      fields.delAll();
      write(bos);
      fa.append(data);
      updateFieldDict();
      valid = true;
    }    
  } else {
    JBlock data = fa.get(0);
    JBlockInputStream bis(data);
    try {
      JObject *obj = read(bis);
      if (obj == this) {
        if (header != "NDBF") return;
        updateFieldDict();
        valid = true;
      } else delete obj;
    } catch (JIllegalArgumentException *e) {
      delete e;
    } catch (JClassReferenceException *e) {
      delete e;
    }
  }
  if (!valid) fa.close();
}

void JDataBase::close() { 
  if (!valid) return;
  updateHeader();
  fa.close();
  valid = false;
}

void JDataBase::updateHeader() {
  if (!valid || fa.isReadOnly()) return;
  JBlock data;
  JBlockOutputStream bos(data);
  write(bos);
  fa.set(0, data);
  fa.updateHeader();
}

int JDataBase::getNumOfField() const { return fields.size();}

int JDataBase::getNextId() { 
  if (!++currentId) ++currentId;
  return currentId;
}

int JDataBase::getSortId() {
  if (!sortId) return sortId;
  if (!getFieldById(sortId)) 
    sortId = 0;
  return sortId;
}

int JDataBase::getSortFieldIndex() {
  int sid = getSortId();
  if (sid) return getFieldById(sid)->current;
  return fields.size();
}

void JDataBase::setSortId(int sid) { 
  if (getFieldById(sid)) 
    sortId = sid;
  else sortId = 0;
  updateHeader();
}

void JDataBase::setSortFieldIndex(int fid) {
  if (fid == fields.size()) setSortId(0);
  else setSortId(getField(fid)->getId());
}

boolean JDataBase::hasField(const JDataField& field) { return fields[field] != null;}
JDataField* JDataBase::getField(int index) { return (JDataField*)fields[index];}
JDataField* JDataBase::getFieldById(int id) 
{ return (JDataField*)OPTR(dict[JInteger(id)]);}

void JDataBase::setField(int index, const JDataField& field) { 
  fields.set(index, field);
  updateFieldDict();
}

void JDataBase::addField(const JDataField& field) 
{ insertField(field);}
void JDataBase::appendField(const JDataField& field) 
{ insertField(field, fields.size());}

void JDataBase::insertField(const JDataField& field, int index) {
  fields.insert(field, index);
  updateFieldDict();
}

void JDataBase::delField(int index, int n) { 
  fields.del(index, n);
  updateFieldDict();
}

void JDataBase::delAllField() { 
  fields.delAll();
  updateFieldDict();
}

void JDataBase::swapField(int a, int b) { 
  fields.swap(a, b);
  updateFieldDict();
}

int JDataBase::size() const { return fa.size()-1;}
int JDataBase::setSize(int ns) { return fa.setSize(ns+1);}
boolean JDataBase::isValid() { return valid && fa.isValid();}
boolean JDataBase::isEmpty() { return (fa.size() < 2);}
boolean JDataBase::isReadOnly() { return fa.isReadOnly();}

void JDataBase::set(int index, const JArray& data) {
  JDataField *df;
  JBlock buf, item;
  int i, sz = fields.size();
  for (i=0; i<sz; i++) {
    df = getField(i);
    item = *(JBlock*)data[i];
    buf+=JBlock(JInteger::toJString(df->getId(), convertBase))+
      JBlock(JInteger::toJString(item.size(), convertBase))+
      item;
  }
  fa.set(index+1, buf);
}

JArray JDataBase::get(int index) {
  JArray result;
  JDataField *df;
  JString str;
  JBlock buf, item;
  JBlockInputStream bis(buf);
  boolean done;
  int id, sz;
  buf = fa.get(index+1);
  result.grow(fields.size(), item);
  do {
    bis >> str;
    done = (str.length() == 0);
    if (!done) {
      id = (int)JInteger(str, convertBase);
      bis >> str;
      sz = (int)JInteger(str, convertBase);
      item = JBlock(sz, 0);
      if (sz > 0) bis >> item;
      df = getFieldById(id);
      if (df) result.set(df->current, item);
    }
  } while (!done);
  return result;
}

void JDataBase::add(const JArray& data) { insert(data);}
void JDataBase::append(const JArray& data) { insert(data, size());}
void JDataBase::insert(const JArray& data, int index) {
  insert(index);
  set(index, data);
}

void JDataBase::insert(int index, int n) 
{ fa.insert(index+1, n);}
void JDataBase::del(int index, int n) 
{ fa.del(index+1, n);}
void JDataBase::delAll() { fa.del(1, size());}
void JDataBase::swap(int a, int b) { fa.swap(a+1, b+1);}
void JDataBase::compact() { fa.compact();}

void JDataBase::updateFieldDict() {
  int i, sz = fields.size();
  JDataField *df;
  dict = JDictionary(101);
  for (i=0; i<sz; i++) {
    df = (JDataField*)fields[i];
    df->current = i;
    dict.add(JInteger(df->getId()), JPObject(df));
  }
  updateHeader();
}

