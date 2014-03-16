#include "JSocketInputStream.h"
#include "JSocket.hpp"
#include "JString.h"
#include "JSocketException.h"

char* theJSocketInputStream = JSocketInputStream().Register();
const char* JSocketInputStream::className() const { return "JSocketInputStream";}
JObject* JSocketInputStream::clone() const { return new JSocketInputStream(*this);}
JSocketInputStream::JSocketInputStream() {}
JSocketInputStream::JSocketInputStream(const JSocket& sock)
  : JDescriptor(sock.getFd()) {}
JSocketInputStream::~JSocketInputStream() { Release();}

JInputStream& JSocketInputStream::operator>>(const JBlock &B) {
  int numBytes = B.size();
  if (!numBytes) return *this;
  if ((numBytes = recv(hnd, B, numBytes, 0)) <= 0) {
    throw new JSocketException("socket read error");
  } else B.setSize(numBytes);
  return *this;
}

JInputStream& JSocketInputStream::operator>>(JString &v) 
{ return JInputStream::operator>>(v);}

