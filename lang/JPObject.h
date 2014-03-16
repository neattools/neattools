#if !defined( _JPObject_h )
#define _JPObject_h

#include "JObject.h"

#define OPTR(x) ((x) ? (JObject*)*(JPObject*)x : null)

class
#include "JBase.hpp"
JPObject : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JPObject(const JObject* _obj = null);
    operator JObject*() const;
  protected:
    JObject *obj;
};

#endif
