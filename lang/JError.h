#if !defined( _JError_h )
#define _JError_h

#include "JThrowable.h"

class
#include "JBase.hpp"
JError : public JThrowable {
  public:
    virtual const char* className() const;
    JError();
    JError(JString message);
};

#endif

