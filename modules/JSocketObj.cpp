#include "JSocketObj.h"
#include "JConvertObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JBlockData.h"
#include "JCharacter.h"
#include "JStringProperty.h"
#include "JIntegerProperty.h"
#include "JSocketException.h"
#include "JUnknownHostException.h"

char* theJSocketObj = JSocketObj().Register();		  
void JSocketObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putObject(os, "address", address);
  putInteger(os, "port", port);
  putInteger(os, "N", N);
}

void JSocketObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  JObject *obj = getObject(dict, "address");
  if (obj) address = *(JString*)obj;
  port = getInteger(dict, "port");
  updateN(getInteger(dict, "N"), false);
}

const char* JSocketObj::className() const { return "JSocketObj";}
JObject* JSocketObj::clone() const { return new JSocketObj(*this);}

JSocketObj::JSocketObj() {
  N = 0;
  updateN(1, false);
  address = "localhost";
  port = 1024;
  setConnected(false);
  enabled = false;
  ssequence = rsequence = 1;
}

JSocketObj::JSocketObj(const JSocketObj& obj) { *this=obj;}
JSocketObj::~JSocketObj() { 
  close();
}

int JSocketObj::isConnected() {
  cs.lock();
  int result = connected;
  cs.unlock();
  return result;
}

void JSocketObj::setConnected(int v) {
  cs.lock();
  connected = v;
  cs.unlock();
}

void JSocketObj::incConnected() {
  cs.lock();
  connected++;
  cs.unlock();
}

void JSocketObj::reset() { 
  setConnected(false);
  data.Dereference();
  socket.close();
}

void JSocketObj::open() {
  cs.lock();
  if (!isConnected()) {
    thread = JThread(this);
    thread.start();
    thread.setPriority(JThread::TNORM_PRIORITY+1);
  }
  cs.unlock();
}

void JSocketObj::close() {
  cs.lock();
  if (isConnected()) {
    setConnected(false);
    thread.setPriority(JThread::TNORM_PRIORITY);
    closeSocket();
    cs.unlock();
    repaint();
    ssequence = rsequence = 1;
  } else cs.unlock();
}

void JSocketObj::openSocket() {
  boolean isIPAddr = true;
  for (int i=0; address[i]; i++) 
    if (JCharacter::isAlpha(address[i]))
      isIPAddr = false;
  if (isIPAddr) {
    JInetAddress inet = JInetAddress(
      JInetAddress::getAddrByJString(address));
    socket = JSocket(inet, port);
    address = inet.getAddressJString();
  } else {
    JInetAddress inet = JInetAddress(address);
    socket = JSocket(inet, port);
    address = inet.getHostName();
  }
}

boolean JSocketObj::connectSocket() {
  if (socket.connect()) {
    sis = JSocketInputStream(socket);
    sos = JSocketOutputStream(socket);
    uchar nN;
    sis >> JBlock(nN);
    updateN(nN, true);
    return true;
  }
  return false;
}

void JSocketObj::closeSocket() {
  try {
    socket.close();
  } catch (JException *e) {
    delete e;
  }
}

int JSocketObj::inputType(int n) { return (n < 2) ? JIntegerData::id : JBlockData::id;}
int JSocketObj::outputType(int n) { return JBlockData::id;} 

void JSocketObj::access(int n, JLinkObj& link, const JDataType& _data) 
{ if (n < N) _data.assign(*data[n]);}
boolean JSocketObj::inputAllowed(int n) { return !inputSet(n).last();}

JString JSocketObj::inputTag(int n) {
  if (n < 2) {
    char* tag[] = { "enable(logical)", "N(1-128)"};
    return tag[n];
  }
  return JString("in-")+JInteger::toJString(n-2);
}

JString JSocketObj::outputTag(int n) 
{ return JString("out-")+JInteger::toJString(n);}

JFRect JSocketObj::inputArea(int n) {
  if (n < 2) return topArea(n, 0, 2);
  return leftArea(n, 2, N, 0, 1);
}

JFRect JSocketObj::outputArea(int n) 
{ return rightArea(n, 0, N, 0, 1);}

int JSocketObj::inputFace(int n) {
  if (n < 2) return TOP;
  return LEFT;
}

JFPoint JSocketObj::inputPoint(int n, JLinkObj& link) {
  if (n < 2) return topPoint(n, link, 0, 2);
  return leftPoint(n, link, 2, N, 0, 1);
}

JFPoint JSocketObj::outputPoint(int n, JLinkObj& link) 
{ return rightPoint(n, link, 0, N, 0, 1);}

void JSocketObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (isConnected() > true) g.setJColor(JColor::red);
    else if (isConnected()) g.setJColor(JColor::yellow);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JSocketObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  drawText(g, "Socket", rect1);
  drawText(g, "Client", rect2);
  drawText(g, address+":"+JInteger::toJString(port), rect3);
}

void JSocketObj::engine(int n, JLinkObj& link) {
  if (!n) {
    link.access(JIntegerData(enabled));
    if (enabled && !isConnected()) open();
    else if (!enabled && isConnected()) close();
  } else if (n == 1) {
    int iv;
    link.access(JIntegerData(iv));
    updateN(iv, true);
  } else {
    cs.lock();
    if (isConnected() > true) {
      try {
        uchar delta = (ssequence+128-rsequence)%128;
        if (delta < 10) {
	  int psize;
	  uchar ch = (uchar)(n-1);
          JBlock data;
          link.access(JBlockData(data));
          psize = data.size();
	  if (psize > 0) {
            sos << JBlock(ssequence)+JBlock(ch)+
	      JBlock(JInteger::toJString(psize, JDataType::convertBase))+data;
            ssequence = (ssequence%128)+1;
	  }
        }
      } catch (JException *e) {
        delete e;
      }
    }
    cs.unlock();
    return;
  }
}

JArray JSocketObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JStringProperty("hostName/IPaddress", address));
  properties.append(JIntegerProperty("port", port, 1024, 5000));
  properties.append(JIntegerProperty("N", N, 1, 128));
  return properties;
}

boolean JSocketObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  boolean changed = false;
  boolean oldenabled = enabled;
  close();
  if (prop.getName() == JString("port")) {
    port = ((JIntegerProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("N")) {
    updateN(((JIntegerProperty*)&prop)->value, true);
    changed = true;
  } else if (prop.getName() == JString("hostName/IPaddress")) {
    address = ((JStringProperty*)&prop)->value;
    changed = true;
  }
  if (oldenabled) open();
  if (changed) repaint();
  return changed;
}

void JSocketObj::processInputStream() {
  while (isConnected() > true) {
    JString str;
    try {
      sis >> str;
      uchar ksequence = (uchar)str[0];
      if (str[1]) { // Generate ACK
        cs.lock();
	uchar ch = 0;
        sos << JBlock(ksequence)+JBlock(ch);
        cs.unlock();
      } else { // Is ACK
        rsequence = ksequence;
        continue;
      }
      int ofs = 0, size;
      int channel = (int)(((uchar)str[1])-1);
      int psize = (int)JInteger(str(2), JDataType::convertBase);
      JBlock buf(psize, 0);
      while (psize > 0) {
        JBlock binary(psize, ((char*)buf)+ofs);
        sis >> binary;
	size = binary.size();
        psize -= size;
	ofs += size;
      }
      data.set(channel, buf);
      broadcast(channel);
    } catch (JException *e) {
      delete e;
      return;
    }
  }
}

void JSocketObj::updateN(int nN, boolean redraw) {
  nN = max(1, min(128, nN));
  if (N != nN) {
    JFRect rect;
    if (redraw) {
      rect = calculateInputUpdate();
      rect |= calculateOutputUpdate();
    }
    N = nN;
    ogm = N;
    igm = N+2;
    for (int i=data.size(); i<N; i++) 
      data.append(JBlock());
    if (redraw) {
      rect |= calculateInputUpdate();
      rect |= calculateOutputUpdate();
      repaintView(rect);
    }
  }
}

void JSocketObj::run() {
RETRY:
  try {
    openSocket();
  } catch (JException *e) {
    delete e;
    closeSocket();
    goto CLOSED;
  }
  setConnected(true);
  repaint();
  try {
    while (isConnected()) {
      if (connectSocket()) break;
      JThread::sleep(100);
    }
    if (!isConnected()) {
      closeSocket();
      setConnected(false);
      repaint();
      goto CLOSED;
    }
  } catch (JException *e) {
    delete e;
    closeSocket();
    if (isConnected()) goto RETRY;
    repaint();
    goto CLOSED;
  }
  incConnected();
  repaint();
  processInputStream();
  if (isConnected() > true) {
    closeSocket();
    goto RETRY;
  }
CLOSED:
  return;
}

