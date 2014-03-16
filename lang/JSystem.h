#if !defined( _JSystem_h )
#define _JSystem_h

#include "JObject.h"

class
#include "JBase.hpp"
JSystem : public JObject {
  public:
    virtual const char* className() const;
    static int currentTimeMillis();
    static void messageBeep();
  private:
    JSystem();
};

#endif
