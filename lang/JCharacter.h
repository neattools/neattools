#if !defined( _JCharacter_h )
#define _JCharacter_h

#include "JString.h"

class
#include "JBase.hpp"
JCharacter : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    static char MIN_VALUE;
    static char MAX_VALUE;
    static int MIN_RADIX;
    static int MAX_RADIX;
    static JString toJString(long i, int radix=10);
    static long parse(JString s, int radix=10);
    static boolean isLowerCase(char ch);
    static boolean isUpperCase(char ch);
    static boolean isDigit(char ch);
    static boolean isSpace(char ch);
    static boolean isAlpha(char ch);
    static char toLowerCase(char ch);
    static char toUpperCase(char ch);
    static int digit(char ch);
    static char forDigit(int digit);
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JCharacter();
    JCharacter(char value);
    JCharacter(JString s);
    operator char&();
    JString toJString();
  private:
    char value;
};

#endif
