#if !defined( _JBoolean_h )
#define _JBoolean_h

#include "JString.h"

class
#include "JBase.hpp"
JBoolean : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static boolean MIN_VALUE;
    static boolean MAX_VALUE;
    static JBoolean TRUE;
    static JBoolean FALSE;
    static JString toJString(boolean i);
    static boolean parse(JString s);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JBoolean();
    JBoolean(boolean value);
    JBoolean(JString s);
    operator boolean&();
    JString toJString();
  private:
    boolean value;
};

#endif
