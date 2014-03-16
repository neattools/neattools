#if !defined( _JDimension_h )
#define _JDimension_h

#include "JObject.h"

class
#include "JAWT.hpp"
JDimension : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDimension();
    JDimension(int width, int height);
    int width, height;
};

#endif
