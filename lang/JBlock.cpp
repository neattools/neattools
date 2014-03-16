#include "JBlock.h"
#include "JString.h"
#include "JCharacter.h"
#include <string.h>

#define PCHAR(x) ((char*)x)
char* theJBlock = JBlock().Register();

void JBlock::writeContent(JOutputStream& os) {
  JReference::writeContent(os);
  putString(os, "value", toJString(*this));
}

void JBlock::readContent(JDictionary& dict) {
  JReference::readContent(dict);
  *this = parse(getString(dict, "value"));
}

JString JBlock::toJString(JBlock b) {
  int i, j;
  char* buf = PCHAR(b.hnd);
  JBlock data(b.sz+b.sz+1, 0);
  for (i=j=0; i<b.sz; i++) {
    data[j++] = JCharacter::forDigit((buf[i] >> 4) & 0xF);
    data[j++] = JCharacter::forDigit(buf[i] & 0xF);
  }
  data[j] = 0;
  return JString(data);
}

JBlock JBlock::parse(JString s) {
  int sz = s.length()/2;
  int current;
  char* buf = (char*)s;
  JBlock dest(sz, 0);
  for (int i=0, j=0; i<sz; i++) {
    current = JCharacter::digit(buf[j++]);
    dest[i] = (char)((current << 4) +
      JCharacter::digit(buf[j++]));
  }
  return dest;
}

static char* duplicate(const char* source, int len) 
{ return (char*)memcpy(new char[len], source, len);}

void JBlock::Delete()
{ delete PCHAR(hnd);}

int JBlock::Duplicate() 
{ return (int)duplicate(PCHAR(hnd), sz);}

const char* JBlock::className() const { return "JBlock";}

int JBlock::hashCode() const {
  int h = 0;
  char* buf = PCHAR(hnd);
  if (sz < 16) {
    for (int i=0; i<sz;)
      h = (h*37)+buf[i++];
  } else {
    int skip = sz/8;
    char *ptr = buf+sz;
    while ((ptr-=skip)>buf)
      h = (h*39)+*ptr;
  }
  return hashMask & h;
}

JObject* JBlock::clone() const { return new JBlock(*this);}

int JBlock::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JReference::compareTo(s);
  JBlock &b = *(JBlock*)&s;
  int result = memcmp(PCHAR(hnd), b, min(sz, b.sz));
  return (result) ? result : sz-b.sz;
}

JBlock::JBlock() { sz = 0;}
JBlock::JBlock(int s, int pad):sz(s), JReference((int)new char[s], true) { memset(PCHAR(hnd), pad, s);}
JBlock::JBlock(int s, char* buf, int ref):sz(s), JReference((int)buf, ref) 
{ if (ref == needCopy) hnd = Duplicate();}
JBlock::JBlock(char &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(uchar &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(short &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(ushort &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(int &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(uint &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(long &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(ulong &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(float &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(double &v):sz(sizeof(v)), JReference((int)&v) {}
JBlock::JBlock(const JString &v, int ref)
  :sz(v.length()+1), JReference((int)(char*)v, ref)
{ if (ref == needCopy) hnd = Duplicate();}
JBlock::~JBlock() { Release();}
JBlock::operator char*() const { return PCHAR(hnd);}
char& JBlock::operator[](int index) const { return PCHAR(hnd)[index];}
JBlock JBlock::operator()(int begin) const
{ return (*this)(begin, sz);}

JBlock JBlock::operator()(int begin, int end) const { 
  int sz = end-begin;
  return JBlock(sz, duplicate(PCHAR(hnd)+begin, sz), true);
}

JBlock& JBlock::operator+=(const JBlock& b) { 
  if (!b.sz) return *this;
  JBlock nB(sz+b.sz, 0);
  if (sz > 0) memcpy(nB, *this, sz);
  memcpy(((char*)nB)+sz, b, b.sz);
  return (*this = nB);
}

JBlock JBlock::operator+(const JBlock& b) const { 
  if (!b.sz) return *this;
  JBlock nB(sz+b.sz, 0);
  if (sz > 0) memcpy(nB, *this, sz);
  memcpy(((char*)nB)+sz, b, b.sz);
  return nB;
}

JBlock& JBlock::grow(int nSize) {
  JBlock nB(nSize, 0);
  nB.copy(*this);
  return *this = nB;
}

JBlock JBlock::insertAt(const JBlock& b, int index) const {
  int sz2 = b.size();
  char* buf = duplicate(PCHAR(hnd), sz+sz2);
  memmove(buf+index+sz2, buf+index, sz-index+1);
  memcpy(buf+index, b, sz2);
  return JBlock(buf, needDel);
}

int JBlock::indexOf(const JBlock& b, int fromIndex) const {
  int result = -1;
  int sz2 = b.size();
  if (sz2 > 0) {
    int smax = sz-sz2;
    char* buf = PCHAR(hnd);
    char* buf2 = (char*)b;
    for (int i=fromIndex; i<sz; i++) {
      if (buf[i] == buf2[0]) {
        if (!memcmp(buf+i, buf2, sz2))
          return i;
      }
    }
  }
  return result;
}

int JBlock::lastIndexOf(const JBlock& b, int fromIndex) const {
  int result = -1;
  int sz2 = b.size();
  if (sz2 > 0) {
    int smax = sz-sz2;
    char* buf = PCHAR(hnd);
    char* buf2 = (char*)b;
    if (fromIndex == -1) fromIndex = sz-sz2-1;
    else if (fromIndex >= smax) return result;
    for (int i=fromIndex; i>=0; i--) {
      if (buf[i] == buf2[0]) {
        if (!memcmp(buf+i, buf2, sz2))
          return i;
      }
    }
  }
  return result;
}

void JBlock::copy(const JBlock& s) const 
{ memcpy(*this, s, s.sz);}

int JBlock::size() const { return sz;}
int JBlock::setSize(int _sz) const { return *(int*)&sz = _sz;}

