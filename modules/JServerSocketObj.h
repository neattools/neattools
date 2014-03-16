#if !defined( _JServerSocketObj_h )
#define _JServerSocketObj_h

#include "JSocketObj.h"
#include "JServerSocket.h"

class JServerSocketObj : public JSocketObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual ~JServerSocketObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void openSocket();
    virtual boolean connectSocket();
    virtual void closeSocket();
    virtual JArray getProperties();
  protected:
    JServerSocket ssocket;
};

#endif
