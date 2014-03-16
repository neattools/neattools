#if !defined( _JRMIDFileObj_h )
#define _JRMIDFileObj_h

#include "JMIDIFileObj.h"

class JRMIDFileObj : public JMIDIFileObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRMIDFileObj();
    ~JRMIDFileObj();
};

#endif
