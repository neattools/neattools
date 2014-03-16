#if !defined( _JObjectPtr_h )
#define _JObjectPtr_h

#include "JPObject.h"

class
#include "JBase.hpp"
JObjectPtr : public JPObject {
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual void forEach(iterFuncType, void** arg=null) const;
    virtual JObject* firstThat(condFuncType, void** arg=null) const;
    virtual JObject* lastThat(condFuncType, void** arg=null) const;
    virtual int compareTo(const JObject& s) const;
    JObjectPtr(const JObject* _obj = null);
};

#endif
