#if !defined( _JMIDIData_h )
#define _JMIDIData_h

#include "JIntegerData.h"

class
#include "JNEAT.hpp"
JMIDIData : public JIntegerData {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JMIDIData(int& _value);
};

#endif
