#if !defined( _JInteger_h )
#define _JInteger_h

#include "JString.h"

class
#include "JBase.hpp"
JInteger : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static int MIN_VALUE;
    static int MAX_VALUE;
    static JString toJString(int i, int radix=10);
    static int parse(JString s, int radix=10);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JInteger();
    JInteger(int value);
    JInteger(JString s, int radix=10);
    operator int&();
    JString toJString();
  private:
    int value;
};

#endif
