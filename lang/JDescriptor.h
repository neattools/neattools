#if !defined( _JDescriptor_h )
#define _JDescriptor_h

#include "JReference.h"

class
#include "JBase.hpp"
JDescriptor : public JReference {
  public:
    virtual const char* className() const;
    JDescriptor();
    JDescriptor(int h, int r=false);
    virtual void Release();
    virtual void Allocate(int handle, int r=true);
    virtual boolean Dereference();
};

#endif
