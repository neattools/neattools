#include "JServerSocket.h"
#include "JSocket.hpp"
#include "JSocketException.h"

#define MAX_PENDING_CONNECTS 5  /* The backlog allowed for listen() */

char* theJServerSocket = JServerSocket().Register();
const char* JServerSocket::className() const { return "JServerSocket";}
JObject* JServerSocket::clone() const { return new JServerSocket(*this);}
JServerSocket::JServerSocket() {}

JServerSocket::JServerSocket(ushort _port) {
  address = JInetAddress::localHost;
  port = _port;
  create(true);
  bind();
}

void JServerSocket::bind() {
  struct sockaddr_in local;
  socklen_t size = sizeof(sockaddr_in);
  local.sin_family = JInetAddress::inetFamily;
  local.sin_addr.s_addr = INADDR_ANY;
  local.sin_port = htons(port);
  if (::bind(hnd, (struct sockaddr*)&local, size) < 0)
    throw new JSocketException("Socket::bind");
  if (::getsockname(hnd, (struct sockaddr*)&local, &size) < 0)
    throw new JSocketException("getsockname");
  port = ntohs(local.sin_port);
}

boolean JServerSocket::listen(int pending) 
{ return (::listen(hnd, pending) == 0);}

boolean JServerSocket::accept(JSocket& socket) {
  struct sockaddr_in their;
  JBlock addr(JInetAddress::addrLen, (char*)&their.sin_addr);
  socklen_t sin_size = sizeof(struct sockaddr_in);
#if defined(WIN32)
  int nfd = ::accept(hnd, (struct sockaddr *)&their, &sin_size);
#else
  int value, nfd;
  ioctl(hnd, FIONBIO, &(value = 1));
  nfd = ::accept(hnd, (struct sockaddr *)&their, &sin_size);
  ioctl(hnd, FIONBIO, &(value = 0));
#endif
  if (nfd == -1) return false;
  addr.Dereference();
  socket = JSocket(nfd, JInetAddress(addr), ntohs(their.sin_port));
  return true;
}
