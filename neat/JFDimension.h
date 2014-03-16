#if !defined( _JFDimension_h )
#define _JFDimension_h

#include "JObject.h"

class
#include "JNEAT.hpp"
JFDimension : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFDimension();
    JFDimension(double width, double height);
    double width, height;
};

#endif
