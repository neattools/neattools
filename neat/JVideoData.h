#if !defined( _JVideoData_h )
#define _JVideoData_h

#include "JBlockData.h"

class
#include "JNEAT.hpp"
JVideoData : public JBlockData {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JVideoData(JBlock& _value);
};

#endif
