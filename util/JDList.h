#if !defined( _JDList_h )
#define _JDList_h

#include "JList.h"

class
#include "JBase.hpp"
JDList : public JList {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void forEach(iterFuncType, void** arg=null) const;
    virtual JObject* firstThat(condFuncType, void** arg=null) const;
    virtual JObject* lastThat(condFuncType, void** arg=null) const;
    virtual int compareTo(const JObject& s) const;
    JDList();
    JDList(const JObject& o);
    virtual ~JDList();
    virtual JObject* toFirst(const JObject& obj);
    virtual JObject* toLast(const JObject& obj);
    virtual JObject* reparent(const JObject& obj, JDList& np);
    virtual JObject* append(const JObject& obj);
    virtual JObject* add(const JObject& obj);
    virtual JObject* replace(const JObject& obj, const JObject& nobj);
    virtual JObject* del(const JObject& obj);
    virtual JObject* del(int index);
    JObject* last();
    virtual void reset(int index=0);
    virtual JObject* current();
    virtual void next();
    virtual void prev();
  protected:
    virtual void Delete();
    virtual int Duplicate();
};

#endif
