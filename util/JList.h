#if !defined( _JList_h )
#define _JList_h

#include "JReference.h"

class
#include "JBase.hpp"
JList : public JReference {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void forEach(iterFuncType, void** arg=null) const;
    virtual JObject* firstThat(condFuncType, void** arg=null) const;
    virtual int compareTo(const JObject& s) const;
    JList();
    JList(const JObject& o);
    virtual ~JList();
    virtual JObject* swap(const JObject& o1, const JObject& o2);
    virtual JObject* add(const JObject& obj);
    virtual JObject* replace(const JObject& obj, const JObject& nobj);
    virtual JObject* del(const JObject& obj);
    virtual JObject* del(int index);
    int indexOf(const JObject& obj);
    JObject* operator[](const JObject& obj);
    JObject* operator[](int index);
    JObject* first();
    boolean isEmpty();
    int size() const;
    virtual void reset(int index=0);
    virtual JObject* current();
    virtual void next();
  protected:
    virtual void Delete();
    virtual int Duplicate();
    void *ptr;
};

#endif
