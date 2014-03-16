#include "JInputStream.h"
#include "JIOException.h"
#include "JBlock.h"
#include "JString.h"

const char* JInputStream::className() const { return "JInputStream";}
long JInputStream::skip(long n) {
  JBlock B(n);
  (*this) >> B;
  return B.size();
}

int JInputStream::available() { return 0;}
void JInputStream::mark(int)
{ throw new JIOException("mark not supported");}
void JInputStream::close() {}
void JInputStream::reset()
{ throw new JIOException("reset not supported");}
boolean JInputStream::markSupported() { return false;}

JInputStream& JInputStream::operator>>(JString &v) {
  int count = 0;
  int size = 80;
  JBlock data(size, 0);
  do {
    if (count == size)
      data.grow(size = size+size);
    (*this) >> data[count];
  } while (data[count++]);
  data.setSize(count);
  v = JString(data);
  return (*this);
}

