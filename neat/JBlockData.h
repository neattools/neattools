#if !defined( _JBlockData_h )
#define _JBlockData_h

#include "JDataType.h"
#include "JBlock.h"

#define JBLOCK(data) ((JBlock&)*(JBlockData*)&data)

class
#include "JNEAT.hpp"
JBlockData : public JDataType {
  public:
    static const int id;
    virtual const char* className() const;
    virtual const char* sid() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JBlockData(JBlock& _value);
    operator JBlock&() const;
    virtual void reset() const;
    virtual void assign(const JObject& obj) const;
  protected:
    JBlock& value;
};

#endif
