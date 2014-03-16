#if !defined( _JLong_h )
#define _JLong_h

#include "JString.h"

class
#include "JBase.hpp"
JLong : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static long MIN_VALUE;
    static long MAX_VALUE;
    static JString toJString(long i, int radix=10);
    static long parse(JString s, int radix=10);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JLong();
    JLong(long value);
    JLong(JString s, int radix=10);
    operator long&();
    JString toJString();
  private:
    long value;
};

#endif
