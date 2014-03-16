#if !defined( _JReference_h )
#define _JReference_h

#include "JObject.h"

class
#include "JBase.hpp"
JReference : public JObject {
  public:
    enum { needDel = 1, needCopy = 2};
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual int compareTo(const JObject& s) const;
    JReference();
    JReference(int h, int r=false);
    JReference(const JReference& s);
    JReference& operator=(const JReference& obj);
    operator int() const;
    virtual void Release();
    virtual void Allocate(int handle, int r=true);
    virtual boolean Dereference();
  protected:
    int hnd;
    int *ref;
    virtual void Delete();
    virtual int Duplicate();
};

#endif
