#if !defined( _JDouble_h )
#define _JDouble_h

#include "JString.h"

class
#include "JBase.hpp"
JDouble : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static double MIN_VALUE;
    static double MAX_VALUE;
    static double EPSILON;
    static JString toJString(double r);
    static JString toJStringF(double r, int w=7, int f=5);
    static double parse(JString s);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JDouble();
    JDouble(double value);
    JDouble(JString s);
    operator double&();
    JString toJString();
  private:
    double value;
};

#endif
