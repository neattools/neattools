#include "JBufferedInputStream.h"
#include "JString.h"
#include "JInterruptedIOException.h"
#include <string.h>

char* theJBufferedInputStream = JBufferedInputStream().Register();
const char* JBufferedInputStream::className() const { return "JBufferedInputStream";}
JObject* JBufferedInputStream::clone() const { return new JBufferedInputStream(*this);}
JBufferedInputStream::JBufferedInputStream()
  : buf(8192, 0) {
  initialize();
}

JBufferedInputStream::JBufferedInputStream(JInputStream &_in) 
  : JFilterInputStream(_in), buf(1024, 0) {
  initialize();
}

void JBufferedInputStream::initialize() {
  count = pos = marklimit = 0;
  markpos = -1;
}

JInputStream& JBufferedInputStream::operator>>(const JBlock &B) {
  int numBytes;
  int total = B.size();
  int current = 0;
  int avail;
  if (total > buf.size()) buf.grow(total*4);
  while (total) {
    JBlock temp(total, ((char*)B)+current);
    avail = count - pos;
    if (avail <= 0) {
      fill();
      avail = count - pos;
      if (avail <= 0)
        throw new JInterruptedIOException("No data available");
    }
    numBytes = min(avail, total);
    memcpy(temp, ((char*)buf)+pos, numBytes);
    pos += numBytes;
    current+=numBytes;
    total-=numBytes;
  }
  return *this;
}

JInputStream& JBufferedInputStream::operator>>(JString &v) 
{ return JFilterInputStream::operator>>(v);}

long JBufferedInputStream::skip(long n) {
  long avail = count - pos;
  if (avail >= n) {
    pos += n;
    return n;
  }
  pos += avail;
  return avail + in->skip(n - avail);
}

int JBufferedInputStream::available() {
  return (count - pos) + in->available();
}

void JBufferedInputStream::mark(int readlimit) { 
  marklimit = readlimit;
  markpos = pos;
}

void JBufferedInputStream::reset() {
  if (markpos < 0) {
    count = pos = marklimit = 0;
    JFilterInputStream::reset();
  } else pos = markpos;
}

boolean JBufferedInputStream::markSupported() { return true;}

void JBufferedInputStream::fill() {
  if (markpos < 0)
    pos = 0;        /* no mark: throw new away the buffer */
  else if (pos >= buf.size()) {    /* no room left in buffer */
    if (markpos > 0) {    /* can throw new away early part of the buffer */
      int sz = pos - markpos;
      memmove(buf, ((char*)buf)+markpos, sz);
      pos = sz;
      markpos = 0;
    } else if (buf.size() >= marklimit) {
      markpos = -1;    /* buffer got too big, invalidate mark */
      pos = 0;    /* drop buffer contents */
    } else buf.grow(min(pos+pos, marklimit));
  }
  JBlock nbuf(buf.size()-pos, ((char*)buf)+pos);
  (*in) >> nbuf;
  count = pos + nbuf.size();
}

