#if !defined( _JWaveData_h )
#define _JWaveData_h

#include "JBlockData.h"

class
#include "JNEAT.hpp"
JWaveData : public JBlockData {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JWaveData(JBlock& _value);
};

#endif
