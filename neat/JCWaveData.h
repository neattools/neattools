#if !defined( _JCWaveData_h )
#define _JCWaveData_h

#include "JBlockData.h"

class
#include "JNEAT.hpp"
JCWaveData : public JBlockData {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JCWaveData(JBlock& _value);
};

#endif
