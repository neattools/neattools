#if !defined( _JCriticalSection_h )
#define _JCriticalSection_h

#include "JReference.h"

class
#include "JBase.hpp"
JCriticalSection : public JReference {
  protected:
    virtual void Delete();
    virtual int Duplicate();
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JCriticalSection();
    virtual ~JCriticalSection();
    virtual void lock();
    virtual void unlock();
#if !defined(WIN32)
  protected:
    int thread, count;
#endif
};

#endif

