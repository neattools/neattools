#if !defined( _JFloat_h )
#define _JFloat_h

#include "JString.h"

class
#include "JBase.hpp"
JFloat : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static float MIN_VALUE;
    static float MAX_VALUE;
    static float EPSILON;
    static JString toJString(float r);
    static float parse(JString s);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFloat();
    JFloat(float value);
    JFloat(JString s);
    operator float&();
    JString toJString();
  private:
    float value;
};

#endif
