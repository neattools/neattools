#if !defined( _JSocket_h )
#define _JSocket_h

#include "JInetAddress.h"
#include "JDescriptor.h"

class
#include "JBase.hpp"
JSocket : public JDescriptor {
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    JSocket();
    JSocket(int fd, const JInetAddress& addr, ushort port);
    JSocket(const JInetAddress& addr, ushort port, boolean stream = true);
    virtual ~JSocket();
    int getFd() const;
    ushort getPort() const;
    JInetAddress getJInetAddress() const;
    void close();
    boolean connect();
  protected:
    ushort port;
    JInetAddress address;
    virtual void Delete();
    void create(boolean stream);
};

#endif
