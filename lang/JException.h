#if !defined( _JException_h )
#define _JException_h

#include "JThrowable.h"

class
#include "JBase.hpp"
JException : public JThrowable {
  public:
    virtual const char* className() const;
    JException();
    JException(JString message);
};

#endif

