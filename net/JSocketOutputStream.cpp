#include "JSocketOutputStream.h"
#include "JSocket.hpp"
#include "JIOException.h"

char* theJSocketOutputStream = JSocketOutputStream().Register();
const char* JSocketOutputStream::className() const { return "JSocketOutputStream";}
JObject* JSocketOutputStream::clone() const { return new JSocketOutputStream(*this);}
JSocketOutputStream::JSocketOutputStream() {}
JSocketOutputStream::JSocketOutputStream(const JSocket& sock)
  : JDescriptor(sock.getFd()) {}

JOutputStream& JSocketOutputStream::operator<<(const JBlock &B) {
  int numBytes = B.size();
  if (!numBytes) return *this;
  if ((numBytes = send(hnd, B, numBytes, 0)) <= 0) {
    throw new JIOException("socket write error");
  } else B.setSize(numBytes);
  return *this;
}

