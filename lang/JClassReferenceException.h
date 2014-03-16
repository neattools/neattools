#if !defined( _JClassReferenceException_h )
#define _JClassReferenceException_h

#include "JIOException.h"

class
#include "JBase.hpp"
JClassReferenceException : public JIOException {
  public:
    virtual const char* className() const;
    JClassReferenceException();
    JClassReferenceException(JString message);
};

#endif

