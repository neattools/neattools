#if !defined( _JThrowable_h )
#define _JThrowable_h

#include "JString.h"

class
#include "JBase.hpp"
JThrowable : public JObject {
  public:
    virtual const char* className() const;
    JThrowable();
    JThrowable(JString message);
    JString getMessage() const;
  private:
    JString detailMessage;
};

#endif

