#include "JServerSocketObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerProperty.h"
#include "JSocketException.h"

char* theJServerSocketObj = JServerSocketObj().Register();
const char* JServerSocketObj::className() const { return "JServerSocketObj";}
JObject* JServerSocketObj::clone() const { return new JServerSocketObj(*this);}
JServerSocketObj::~JServerSocketObj() { close();}

void JServerSocketObj::openSocket() { 
  ssocket = JServerSocket(port);
  if (!ssocket.listen(1))
    throw new JSocketException("listen");
}

boolean JServerSocketObj::connectSocket() {
  if (ssocket.accept(socket)) {
    ssocket.close();
    uchar nN = (uchar)N;
    sis = JSocketInputStream(socket);
    sos = JSocketOutputStream(socket);
    sos << JBlock(nN);
    return true;
  }
  return false;
}

void JServerSocketObj::closeSocket() {
  try {
    socket.close();
    ssocket.close();
  } catch (JIOException *e) {
    delete e;
  }
}

void JServerSocketObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  drawText(g, "Socket", rect1);
  drawText(g, "Server", rect2);
  drawText(g, JString("Port:")+JInteger::toJString(port), rect3);
}

JArray JServerSocketObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerProperty("port", port, 1024, 5000));
  properties.append(JIntegerProperty("N", N, 1, 128));
  return properties;
}		 

