#if !defined( _JComplex_h )
#define _JComplex_h

#include "JString.h"
#include "bcomplex.h"

class
#include "JBase.hpp"
JComplex : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static JString toJString(const jcomplex& c);
    static JString toJStringH(const jcomplex& c);
    static JString toJStringF(const jcomplex& c, int w=7, int f=5);
    static jcomplex parse(JString s);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JComplex();
    JComplex(const jcomplex& _value);
    JComplex(JString s);
    operator jcomplex&();
    JString toJString();
  private:
    jcomplex value;
};

#endif
