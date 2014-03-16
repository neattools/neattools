#include "JBlockInputStream.h"
#include "JIOException.h"
#include "JString.h"
#include "JBlock.h"

char* theJBlockInputStream = JBlockInputStream().Register();
const char* JBlockInputStream::className() const { return "JBlockInputStream";}
JObject* JBlockInputStream::clone() const { return new JBlockInputStream(*this);}

JBlockInputStream::JBlockInputStream() : in(null) { 
  pos = marklimit = 0;
  markpos = -1;
}

JBlockInputStream::JBlockInputStream(JBlock &_in) : in(&_in) {
  pos = marklimit = 0;
  markpos = -1;
}

void JBlockInputStream::connect(JBlock &_in) { 
  in = &_in;
  pos = marklimit = 0;
  markpos = -1;
}

JInputStream& JBlockInputStream::operator>>(const JBlock &B) {
  long delta=min(B.size(), available());
  B.copy(JBlock(delta, ((char*)*in)+pos));
  B.setSize(delta);
  pos+=delta;
  return *this;
}

JInputStream& JBlockInputStream::operator>>(JString &v)
{ return JInputStream::operator>>(v);}

long JBlockInputStream::skip(long n) { 
  long delta=min(n, available()); 
  pos+=delta;
  return delta;
}

int JBlockInputStream::available() { return in->size()-pos;}

void JBlockInputStream::mark(int readLimit) { 
  marklimit = readLimit;
  markpos = pos;
}

void JBlockInputStream::reset() { 
  if (markpos < 0) {
    pos = marklimit = 0;
    JInputStream::reset();
  } else pos = markpos;
}

boolean JBlockInputStream::markSupported() { return true;}

