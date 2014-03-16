#if !defined( _JServerSocket_h )
#define _JServerSocket_h

#include "JSocket.h"

class
#include "JBase.hpp"
JServerSocket : public JSocket {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JServerSocket();
    JServerSocket(ushort port);
    boolean listen(int pending = 4);
    boolean accept(JSocket& socket);
  protected:
    void bind();
};

#endif
