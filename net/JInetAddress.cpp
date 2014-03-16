#include "JSocket.hpp"
#include "JInetAddress.h"
#include "JUnknownHostException.h"
#include "JDictionary.h"
#include "JAssociation.h"
#include <stdio.h>

int JInetAddress::addrLen = 4;
short JInetAddress::inetFamily = AF_INET;

#if defined(WIN32)
  class WinSock {
    public :
      WinSock() {
        WSADATA WSAData;
        WSAStartup(MAKEWORD(1,1), &WSAData);
      }
      ~WinSock() { WSACleanup();}
  } winsock;
#endif

JDictionary lookup(101);
JInetAddress JInetAddress::localHost("localhost", 
  getAddrByJString("127.0.0.1"));
char* theJInetAddress = JInetAddress().Register();

void JInetAddress::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putObject(os, "hostName", hostName);
  putObject(os, "address", address);
}

void JInetAddress::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  hostName = *(JString*)getObject(dict, "hostName");
  address = *(JBlock*)getObject(dict, "address");
}

const char* JInetAddress::className() const { return "JInetAddress";}
int JInetAddress::hashCode() const
{ return hashMask & (int)(*this);}
JObject* JInetAddress::clone() const { return new JInetAddress(*this);}

int JInetAddress::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return (int)(*this)-(int)*(JInetAddress*)&s;
}

JInetAddress::JInetAddress() { *this = localHost;}

JInetAddress::JInetAddress(const JString& name) 
{ *this = getByName(name);}

JInetAddress::JInetAddress(const JBlock& addr) 
  : address(addr) {}

JInetAddress::JInetAddress(const JString& name, const JBlock& addr)
  : hostName(name), address(addr) {
  lookup.add(hostName, address);
  lookup.add(address, hostName);
}

JInetAddress::operator int&() const { 
  return *(int*)(char*)address;
}

JString JInetAddress::getHostName() {
  if (!hostName.length()) {
    try {
      hostName = getByAddr(address).hostName;
    } catch (JUnknownHostException *e) {
      hostName = getJStringByAddr(address);
      delete e;
    }
  }
  return hostName;
}

JBlock JInetAddress::getAddress() { return address;}

JString JInetAddress::getAddressJString() 
{ return getJStringByAddr(address);}

JInetAddress JInetAddress::getByName(const JString& host) {
  if (!host.length()) return localHost;
  struct hostent *phe;
  JObject *obj = lookup[host];
  if (obj) return JInetAddress(host, *(JBlock*)obj);
  if ((phe = gethostbyname((char*)host)) != NULL) {
#if defined(WIN32)
    JBlock addr(addrLen, phe->h_addr, JReference::needCopy);
    return JInetAddress(host, addr);
#else
    JString name(phe->h_name, JReference::needCopy);
    JBlock addr(addrLen, phe->h_addr, JReference::needCopy);
    return JInetAddress(name, addr);
#endif
  }
  throw new JUnknownHostException("JInetAddress::getByName");
  return JInetAddress();
}

JInetAddress JInetAddress::getByAddr(const JBlock& addr) {
  if (!(*(int*)(char*)addr)) return localHost;
  struct hostent *phe;
  JObject* obj = lookup[addr];
  if (obj) return JInetAddress(*(JString*)obj, addr);
  if ((phe = gethostbyaddr(addr, addrLen, inetFamily)) != NULL) {
    JString name(phe->h_name, JReference::needCopy);
    JBlock addr(addrLen, phe->h_addr, JReference::needCopy);
    return JInetAddress(name, addr);
  }
  throw new JUnknownHostException("JInetAddress::getByAddr");
#if !defined(BC5)
  return JInetAddress();
#endif
}

JString JInetAddress::getJStringByAddr(const JBlock& addr) {
  JString result(inet_ntoa(*(struct in_addr*)(char*)addr),
    JReference::needCopy);
  return result;
}

JBlock JInetAddress::getAddrByJString(const JString& addr) {
  int i = inet_addr(addr);
  JBlock ip(i);
  ip.Dereference();
  return ip;
}


JArray JInetAddress::getAllByName(const JString& host) {
  struct hostent *phe;
  if (!host.length())
    throw new JUnknownHostException("JInetAddress::getAllByName");
  if ((phe = gethostbyname(host)) != NULL) {
    JString name;
    JBlock addr;
    int i, count = 0;
    while (phe->h_aliases[count] != NULL)
      count++;
    JArray result(count);
    for (i=0; i<count; i++) {
      name = JString(phe->h_aliases[i], JReference::needCopy);
      addr = JBlock(addrLen, phe->h_addr_list[i], JReference::needCopy);
      result.set(i, JInetAddress(name, addr));
    }
    return result;
  }
  throw new JUnknownHostException("JInetAddress::getAllByName");
#if !defined(BC5)
  return JArray();
#endif
}

