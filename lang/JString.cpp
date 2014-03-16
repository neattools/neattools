#include "JString.h"
#include "JBlock.h"
#include "JInteger.h"
#include "JFloat.h"
#include "JDouble.h"
#include <ctype.h>
#include <string.h>

#define STR(x) ((char*)x)
char* theJString = JString().Register();

void JString::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putString(os, "value", (char*)*this);
}

void JString::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  *this = getString(dict, "value");
  Dereference();
}

static int strcasecmp(const char* s, const char* t) {
  for (;*s && (toupper(*s) == toupper(*t)); s++, t++);
  return (toupper(*s)-toupper(*t));
}

static char* allocate(int len) {
  char* buf = new char[len+1];
  buf[len] = 0;
  return buf;
}

static char* duplicate(const char* source) 
{ return strcpy(allocate(strlen(source)), source);}

static char* duplicate(const char* source, int len) 
{ return strncpy(allocate(len), source, len);}

static char* concatenate(const char* dest, const char* source) {
  if (!*dest) return duplicate(source);
  if (!*source) return duplicate(dest);
  return strcat(strcpy(allocate(strlen(dest)+strlen(source)),
    dest), source);
}

void JString::Delete() 
{ delete STR(hnd);}

int JString::Duplicate() 
{ return (int)duplicate(STR(hnd));}

const char* JString::className() const { return "JString";}

int JString::hashCode() const {
  int h = 0;
  char* str = STR(hnd);
  int len = strlen(str);
  if (len < 16) {
    char *ptr = str;
    while (*ptr)
      h = (h*37)+*ptr++;
  } else {
    int skip = len/8;
    char *ptr = str+len;
    while ((ptr-=skip)>str)
      h = (h*39)+*ptr;
  }
  return hashMask & h;
}

JObject* JString::clone() const { return new JString(*this);}

int JString::compareTo(const JObject& s) const { 
  if (className() != s.className()) 
    return JReference::compareTo(s);
  return strcmp(STR(hnd), *(JString*)&s);
}

JString::JString():JReference((int)EMPTY) {}
/* ref 0 : reference, ref 1 : needDel, ref 2 : needCopy */
JString::JString(const char* s, int ref):JReference((int)s, ref) 
{ if (ref == needCopy) hnd = Duplicate();}
JString::JString(const JBlock& B):JReference(0, needDel) {
  int sz = B.size();
  char *data = new char[sz+1];
  memcpy(data, B, sz);
  data[sz] = 0;
  hnd = (int)data;
}

JString::~JString() { Release();}
JString::operator char*() const { return STR(hnd);}
char& JString::operator[](int index) const { return STR(hnd)[index];}
JString JString::operator()(int begin) const 
{ return JString(duplicate(STR(hnd)+begin), needDel);}
JString JString::operator()(int begin, int end) const 
{ return JString(duplicate(STR(hnd)+begin, end-begin), needDel);}

JString& JString::operator+=(const JString& s)
{ return (*this = JString(concatenate(STR(hnd), s), needDel));}

JString JString::operator+(const JString& s) const
{ return JString(concatenate(STR(hnd), s), needDel);}

JString& JString::operator+=(char* str)
{ return (*this = JString(concatenate(STR(hnd), str), needDel));}

JString JString::operator+(char* str) const
{ return JString(concatenate(STR(hnd), str), needDel);}

JString JString::operator+(const char* str) const
{ return JString(concatenate(STR(hnd), str), needDel);}

JString& JString::operator+=(char val)
{ return (*this)+=JString(JBlock(val));}

JString JString::operator+(char val) const
{ return (*this)+JString(JBlock(val));}

JString& JString::operator+=(int val)
{ return (*this)+=JInteger::toJString(val);}

JString JString::operator+(int val) const
{ return (*this)+JInteger::toJString(val);}

JString& JString::operator+=(float val)
{ return (*this)+=JFloat::toJString(val);}

JString JString::operator+(float val) const
{ return (*this)+JFloat::toJString(val);}

JString& JString::operator+=(double val)
{ return (*this)+=JDouble::toJString(val);}

JString JString::operator+(double val) const
{ return (*this)+JDouble::toJString(val);}

boolean JString::operator==(const JString& s) const { return strcmp(STR(hnd), s) == 0;}
boolean JString::operator!=(const JString& s) const { return strcmp(STR(hnd), s) != 0;}
boolean JString::operator>=(const JString& s) const { return strcmp(STR(hnd), s) >= 0;}
boolean JString::operator<=(const JString& s) const { return strcmp(STR(hnd), s) <= 0;}
boolean JString::operator> (const JString& s) const { return strcmp(STR(hnd), s) >  0;}
boolean JString::operator< (const JString& s) const { return strcmp(STR(hnd), s) <  0;}

boolean JString::operator==(char* str) const { return strcmp(STR(hnd), str) == 0;}
boolean JString::operator!=(char* str) const { return strcmp(STR(hnd), str) != 0;}
boolean JString::operator>=(char* str) const { return strcmp(STR(hnd), str) >= 0;}
boolean JString::operator<=(char* str) const { return strcmp(STR(hnd), str) <= 0;}
boolean JString::operator> (char* str) const { return strcmp(STR(hnd), str) >  0;}
boolean JString::operator< (char* str) const { return strcmp(STR(hnd), str) <  0;}

boolean JString::operator==(const char* str) const { return strcmp(STR(hnd), str) == 0;}
boolean JString::operator!=(const char* str) const { return strcmp(STR(hnd), str) != 0;}
boolean JString::operator>=(const char* str) const { return strcmp(STR(hnd), str) >= 0;}
boolean JString::operator<=(const char* str) const { return strcmp(STR(hnd), str) <= 0;}
boolean JString::operator> (const char* str) const { return strcmp(STR(hnd), str) >  0;}
boolean JString::operator< (const char* str) const { return strcmp(STR(hnd), str) <  0;}

int JString::length() const { return strlen(STR(hnd));}

boolean JString::equalsIgnoreCase(char* str) const
{ return strcasecmp(STR(hnd), str) == 0;}

int JString::compareIgnoreCaseTo(char* str) const
{ return strcasecmp(STR(hnd), str);}

JString JString::toLowerCase() const {
  char* str = STR(hnd);
  int len = strlen(str);
  char* buf = allocate(len);
  for (int i=len; i-->0; buf[i] = (char)tolower(str[i]));
  return JString(buf, needDel);
}

JString JString::toUpperCase() const {
  char* str = STR(hnd);
  int len = strlen(str);
  char* buf = allocate(len);
  for (int i=len; i-->0; buf[i] = (char)toupper(str[i]));
  return JString(buf, needDel);
}

JString JString::trim() const {
  char* str = STR(hnd);
  int right = strlen(str)-1;
  int left = 0;
  while (str[left] == ' ') left++;
  if (left <= right)
    while ((right > -1) && (str[right] == ' ')) right--;
  return (*this)(left, right+1);
}

JString JString::insertAt(char ch, int index) const {
  int len = length();
  char* buf = duplicate(STR(hnd), len+1);
  memmove(buf+index+1, buf+index, len-index+1);
  buf[index] = ch;
  return JString(buf, needDel);
}

JString JString::insertAt(char* s, int index) const {
  int len = length();
  int len2 = strlen(s);
  char* buf = duplicate(STR(hnd), len+len2);
  memmove(buf+index+len2, buf+index, len-index+1);
  memcpy(buf+index, s, len2);
  return JString(buf, needDel);
}

JString JString::insertAt(const JString& s, int index) const {
  return insertAt((char*)s, index);
}

int JString::indexOf(char ch, int fromIndex) const {
  char *ptr = strchr(STR(hnd)+fromIndex, ch);
  return (ptr) ? ptr-STR(hnd) : -1;
}

int JString::indexOf(char* str, int fromIndex) const {
  char *ptr = strstr(STR(hnd)+fromIndex, str);
  return (ptr) ? ptr-STR(hnd) : -1;
}

int JString::indexOf(const JString& s, int fromIndex) const {
  return indexOf((char*)s, fromIndex);
}

int JString::lastIndexOf(char ch, int fromIndex) const {
  char *ptr = STR(hnd);
  if (fromIndex == -1) fromIndex = length()-1;
  for (int i=fromIndex; i>=0; i--)
    if (ptr[i] == ch) return i;
  return -1;
}

int JString::lastIndexOf(char* str, int fromIndex) const {
  char *ptr = STR(hnd);
  int len = strlen(str);
  if (!len) return -1;
  if (fromIndex == -1) fromIndex = length()-1;
  for (int i=fromIndex-len+1; i>=0; i--)
    if (!strncmp(ptr+i, str, len)) return i;
  return -1;
}

int JString::lastIndexOf(const JString& str, int fromIndex) const {
  return lastIndexOf((char*)str, fromIndex);
}

JString JString::token(char* seps, int& index) const {
  char *buf = STR(hnd);
  while (strchr(seps, buf[index])) index++;
  if (!buf[index]) return JString("");
  int base = index;
  while (buf[index] && 
    !strchr(seps, buf[index])) index++;
  return JString(JBlock(index-base, buf+base));
}
