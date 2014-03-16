#include "JBufferedOutputStream.h"
#include "JIOException.h"
#include <string.h>

char* theJBufferedOutputStream = JBufferedOutputStream().Register();
const char* JBufferedOutputStream::className() const { return "JBufferedOutputStream";}
JObject* JBufferedOutputStream::clone() const { return new JBufferedOutputStream(*this);}
JBufferedOutputStream::JBufferedOutputStream()
  : buf(8192, 0) {
  initialize();
}

JBufferedOutputStream::JBufferedOutputStream(JOutputStream &_out) 
  : JFilterOutputStream(_out), buf(1024, 0) {
  initialize();
}

JBufferedOutputStream::~JBufferedOutputStream() { flush();}

void JBufferedOutputStream::initialize() {
  count = 0;
}

JOutputStream& JBufferedOutputStream::operator<<(const JBlock &B) {
  int numBytes = B.size();
  int avail = buf.size() - count;
  if (!numBytes) return *this;
  if (numBytes <= avail) {
    memcpy(((char*)buf)+count, B, numBytes);
    count += numBytes;
    return *this;
  }
  flush();
  (*out) << B;
  return *this;
}

void JBufferedOutputStream::flush() {
  if (!out) return;
  if (count > 0) {
    (*out) << JBlock(count, (char*)buf);
    count = 0;
  }
  out->flush();
}

