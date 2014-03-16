#include "JDescriptor.h"

char* theJDescriptor = JDescriptor().Register();
const char* JDescriptor::className() const { return "JDescriptor";}
JDescriptor::JDescriptor() : JReference(-1) {}
JDescriptor::JDescriptor(int h, int r)
  : JReference(h, r) {}

boolean JDescriptor::Dereference() {
  if (!ref || (*ref > 1)) {
    int old = hnd;
    if ((hnd != -1) && Duplicate()) {
      if (ref) --(*ref);
      *(ref = new int) = 1;
      return true;
    } else hnd = old;
  }
  return false;
}

void JDescriptor::Release() {
  if (ref && (--(*ref) == null)) {
    delete ref;
    if (hnd != -1) Delete();
  }
  ref = null;
  hnd = -1;
}

void JDescriptor::Allocate(int handle, int r) {
  if (hnd != -1) Release();
  ref=(r)?&((*new int)=1):null;
  hnd = handle;
}

