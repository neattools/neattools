#include "JCharacter.h"
#include "JBlock.h"
#include <limits.h>

#define MAX_BUF 32

char JCharacter::MIN_VALUE = CHAR_MIN;
char JCharacter::MAX_VALUE = CHAR_MAX;
int JCharacter::MIN_RADIX = 2;
int JCharacter::MAX_RADIX = 128;
char* theJCharacter = JCharacter().Register();

void JCharacter::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "value", (int)value);
}

void JCharacter::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  value = (char)getInteger(dict, "value");
}

JString JCharacter::toJString(long i, int radix) {
  JBlock buf(MAX_BUF, 0);
  int digitCount = 0;
  if (i < 0) {
    while (i <= -radix) {
      buf[MAX_BUF-++digitCount]
	= forDigit(-(i%radix));
      i /= radix;
    }
    buf[MAX_BUF-++digitCount] = forDigit(-i);
    buf[MAX_BUF-++digitCount] = '-';
  } else {
    while (i >= radix) {
      buf[MAX_BUF-++digitCount]
        = forDigit((i % radix));
      i /= radix;
    }
    buf[MAX_BUF-++digitCount] = forDigit(i);
  }
  if (digitCount) {
    int delta = MAX_BUF-digitCount;
    for (int j=0; j<digitCount; j++)
      buf[j] = buf[j+delta];
    buf.setSize(digitCount);
    return JString(buf);
  } else return JString("0");
}

long JCharacter::parse(JString s, int radix) {
  long result = 0;
  boolean negative = false;
  int i=0, max = s.length();
  if (radix < 36) s = s.toUpperCase();
  if (max > 0) {
    if (s[0] == '-') {
      negative = true;
      i++;
    }
    while (i < max)
      result = result*radix+digit(s[i++]);
  }
  return (negative) ? -result : result;
}

boolean JCharacter::isLowerCase(char ch)
{ return ('a' <= ch) && (ch <= 'z');}
boolean JCharacter::isUpperCase(char ch)
{ return ('A' <= ch) && (ch <= 'Z');}
boolean JCharacter::isDigit(char ch)
{ return ('0' <= ch) && (ch <= '9');}
boolean JCharacter::isAlpha(char ch)
{ return ('a' <= ch) && (ch <= 'z') || ('A' <= ch) && (ch <= 'Z');}
boolean JCharacter::isSpace(char ch) {
  switch (ch) {
    case ' ':
    case '\t':
    case '\f': // form feed
    case '\n':
    case '\r':
      return true;
  }
  return false;
}

char JCharacter::toLowerCase(char ch)
{ return isUpperCase(ch) ? ch+'a'-'A' : ch;}
char JCharacter::toUpperCase(char ch)
{ return isLowerCase(ch) ? ch-'a'+'A' : ch;}

char JCharacter::forDigit(int digit) {
  if (digit < 10) return (char)('0'+digit);
  return (char)('A'+digit-10);
}

int JCharacter::digit(char ch) {
  int n = (uchar)ch;
  if (n < '0') return -1;
  if (n <= '9') return (n-'0');
  if (n >= 'A') return (10+n-'A');
  return -1;  
}

const char* JCharacter::className() const { return "JCharacter";}

int JCharacter::hashCode() const
{ return hashMask & (int)value;}
JObject* JCharacter::clone() const { return new JCharacter(*this);}

int JCharacter::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return value-((JCharacter*)&s)->value;
}

JCharacter::JCharacter() : value('\0') {}
JCharacter::JCharacter(char _value) : value(_value) {}
JCharacter::JCharacter(JString s) : value(s[0]) {}

JCharacter::operator char&() { return value;}
JString JCharacter::toJString() { return JString(JBlock(value));}

