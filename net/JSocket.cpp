#include "JSocket.h"
#include "JSocket.hpp"
#include "JSocketException.h"

char* theJSocket = JSocket().Register();
void JSocket::Delete() { closesocket(hnd);}
const char* JSocket::className() const { return "JSocket";}
int JSocket::hashCode() const { return JReference::hashCode();}
JObject* JSocket::clone() const { return new JSocket(*this);}
JSocket::JSocket() : port(0) {}

JSocket::JSocket(int _fd, const JInetAddress& addr, ushort _port)
  : JDescriptor(_fd, true), address(addr), port(_port) {}

JSocket::JSocket(const JInetAddress& addr, ushort _port, boolean stream)
  : address(addr), port(_port) {
  create(stream);
}

JSocket::~JSocket() { Release();}
int JSocket::getFd() const { return hnd;}
ushort JSocket::getPort() const { return port;}
JInetAddress JSocket::getJInetAddress() const { return address;}

void JSocket::close() {
  Release();
}

void JSocket::create(boolean stream) {
  Allocate(socket(JInetAddress::inetFamily,
    (stream ? SOCK_STREAM : SOCK_DGRAM), 0));
  if (hnd == -1) throw new JSocketException("invalid socket");
}

boolean JSocket::connect() {
  struct sockaddr_in dest;
  JBlock data(JInetAddress::addrLen, (char*)&dest.sin_addr);
  data.copy(address.getAddress());
  dest.sin_family = JInetAddress::inetFamily;
  dest.sin_port = htons(port);
  return (::connect(hnd, (struct sockaddr*)&dest, sizeof(dest)) == 0);
}

