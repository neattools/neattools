#include "JReference.h"

char* theJReference = JReference().Register();
const char* JReference::className() const { return "JReference";}
int JReference::hashCode() const { return hashMask & hnd;}

int JReference::compareTo(const JObject& s) const {
  if (className() != s.className()) 
    return JObject::compareTo(s);
  return hnd-((JReference*)&s)->hnd;
}

JReference::JReference() : hnd(null), ref(null) {}

JReference::JReference(int h, int r) : hnd(h) 
{ ref=(r)?&((*new int)=1):null;}

JReference::JReference(const JReference& s) 
  : hnd(null), ref(null)
{ *this=s;}

JReference& JReference::operator=(const JReference& obj) {
  if (hnd != obj.hnd) {
    Release();
    ref = obj.ref;
    if (ref) (*ref)++;
    hnd = obj.hnd;
  }
  return *this;
}

JReference::operator int() const { return hnd;}

void JReference::Release() {
  if (ref && (--(*ref) == null)) {
    delete ref;
    if (hnd) Delete();
  }
  ref = null;
  hnd = null;
}

void JReference::Allocate(int handle, int r) {
  if (hnd) Release();
  if (handle) {
    ref=(r)?&((*new int)=1):null;
    hnd = handle;
  }
}

boolean JReference::Dereference() {
  if (!ref || (*ref > 1)) {
    int old = hnd;
    if (hnd && ((hnd=Duplicate()) != 0)) {
      if (ref) --(*ref);
      *(ref = new int) = 1;
      return true;
    } else hnd = old;
  }
  return false;
}

void JReference::Delete() {};
int JReference::Duplicate() { return false;}

