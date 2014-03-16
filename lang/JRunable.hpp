#if !defined( _JRunnable_h )
#define _JRunnable_h

#include "JObject.h"

class
#if defined(_BASE_DLL)
  DllExport
#else
  DllImport 
#endif
JRunnable {
  public:
    virtual void run() = null;
};

#endif

