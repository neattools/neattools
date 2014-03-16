#if !defined( _JCVideoData_h )
#define _JCVideoData_h

#include "JBlockData.h"

class
#include "JNEAT.hpp"
JCVideoData : public JBlockData {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    JCVideoData(JBlock& _value);
};

#endif
