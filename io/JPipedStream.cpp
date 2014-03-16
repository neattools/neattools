#include "JPipedStream.h"
#include "JIOException.h"
#include <string.h>

char* theJPipedStream = JPipedStream().Register();
const char* JPipedStream::className() const { return "JPipedStream";}
JObject* JPipedStream::clone() const { return new JPipedStream(*this);}
JPipedStream::JPipedStream() : buf(1024, 0) {
  count = pos = 0;
}

JInputStream& JPipedStream::operator>>(const JBlock &B) {
  if ((count-pos) < B.size())
    throw new JIOException("No data available.");
  memcpy(B, ((char*)buf)+pos, B.size());
  pos += B.size();
  return *this;
}

JInputStream& JPipedStream::operator>>(JString &v)
{ return JInputStream::operator>>(v);}

long JPipedStream::skip(long n) {
  long x = n;
  while (x) {
    long avail = count - pos;
    if (avail >= x) {
      pos += x;
      break;
    } else if (avail) {
      pos += avail;
      x -= avail;
    }
  }
  return n;
}

int JPipedStream::available() { return (count - pos);}

JOutputStream& JPipedStream::operator<<(const JBlock &B) {
  if (B.size() > buf.size()) buf.grow(B.size());
  while (B.size()+count > buf.size())
    flush();
  memcpy(((char*)buf)+count, B, B.size());
  count += B.size();
  return *this;
}

void JPipedStream::flush() {
  if (pos) {
    memmove(buf, ((char*)buf)+pos, count-pos);
    count -= pos;
    pos = 0;
  }
}
