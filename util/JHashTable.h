#if !defined( _JHashTable_h )
#define _JHashTable_h

#include "JArray.h"

class
#include "JBase.hpp"
JHashTable : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void forEach(iterFuncType, void** arg = null) const;
    virtual JObject* firstThat(condFuncType, void** arg = null) const;
    virtual int compareTo(const JObject& s) const;
    JHashTable();
    JHashTable(int sz);
    JObject* operator[](const JObject& obj);
    JObject* add(const JObject& obj);
    JObject* del(const JObject& obj);
    int size() const;
    int count() const;
    void rehash(int sz);
    void Dereference();
    void Release();
  protected:
    JArray entry;
};

#endif
