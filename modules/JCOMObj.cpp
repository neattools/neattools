#include "JCOMObj.h"
#include "JThread.h"
#include "JLinkObj.h"
#include "JMessageBox.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JBytesData.h"

#define FC_DTRECTSD (0x1000)
#define MIN_COM_PORT 1
#define MAX_COM_PORT 99

char* theJCOMObj = JCOMObj().Register();
enum { t_COM, t_LPT};
enum { s_Default, s_110, s_300, s_600, s_1200, 
  s_2400, s_4800, s_9600, s_14400, s_19200, 
  s_38400, s_56000, s_57600, s_115200, s_125000, s_128000, s_256000};
// s_125000 added PDG


enum { p_Default, p_None, p_Event, p_Odd, p_Mark};
enum { d_Default, d_Five, d_Six, d_Seven, d_Eight};
enum { b_Default, b_One, b_One5, b_Two};
enum { f_Default, f_DTRDSR, f_RTSCTS, f_XONXOFF, f_DTRECTSD};

char* typeTag[] = { "COM", "LPT", null}; 
// Changed for new syntax for COM ports > 9 (also works for 1-9)
char* typeTag2[] = { "\\\\.\\COM", "LPT", null };
// Use this for opening port; use regular tag for other labels

char* speedTag[] = { "Default (19200)", "100", "300", "600", "1200", 
  "2400", "4800", "9600", "14400", "19200", "38400", 
  "56000", "57600", "115200", "125000", "128000", "256000", null};
// "125000" added
char* parityTag[] = { "Default (None)", "None", "Event", "Odd", "Mark", null};
char* databitsTag[] = { "Default (8)", "5", "6", "7", "8", null};
char* stopbitsTag[] = { "Default (1)", "1", "1.5", "2", null};
char* flowControlTag[] = { "Default (None)", 
  "None", "DTRDSR", "RTSCTS", "XONXOFF", "DTREnableCTSDisable", null};
#define BUFFER_SIZE 8192

void JCOMObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "type", type);
  putInteger(os, "port", port);
  putInteger(os, "speed", speed);
  putInteger(os, "parity", parity);
  putInteger(os, "databits", databits);
  putInteger(os, "stopbits", stopbits);
  putInteger(os, "flowControl", flowControl);
}

void JCOMObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  type = getInteger(dict, "type");
  port = getInteger(dict, "port");
  speed = getInteger(dict, "speed");
  parity = getInteger(dict, "parity");
  databits = getInteger(dict, "databits");
  stopbits = getInteger(dict, "stopbits");
  flowControl = getInteger(dict, "flowControl");
  port = max(MIN_COM_PORT, min(MAX_COM_PORT, port));
}

const char* JCOMObj::className() const { return "JCOMObj";}
JObject* JCOMObj::clone() const { return new JCOMObj(*this);}

JCOMObj::JCOMObj(int _port) {
  igm = IN_LAST;
  type = t_COM;
  port = _port;
  handle = -1;
  connected = false;
  speed = parity = databits = stopbits = 0;
  flowControl = 0;
  bufferSize = 4096;
  enabled = false;
  samplingClock = false;
}

JCOMObj::~JCOMObj() { 
  close();
}

void JCOMObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JCOMObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString(typeTag[type])+JInteger::toJString(port), rect);
}

void JCOMObj::access(int n, JLinkObj& link, const JDataType& _data) 
{ _data.assign(data);}

int JCOMObj::inputType(int n) 
{ return (!n) ? JBytesData::id : JIntegerData::id;}
int JCOMObj::outputType(int n) { return JBytesData::id;}
boolean JCOMObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JCOMObj::inputTag(int n) {
  char* tag[] = {"input", "enabled(logical)", 
    "sampling_clock(logical)"};
  return tag[n];
}

JFRect JCOMObj::inputArea(int n) {
  if (!n) return leftArea(n, 0, 1);
  return topArea(n, 1, IN_LAST-1);
}

JFPoint JCOMObj::inputPoint(int n, JLinkObj& link) {
  if (!n) return leftPoint(n, link, 0, 1);
  return topPoint(n, link, 1, IN_LAST-1);
}

#if defined(WIN32)
  #include <windows.h>

  #define ASCII_BEL       0x07
  #define ASCII_BS        0x08
  #define ASCII_LF        0x0A
  #define ASCII_CR        0x0D
  #define ASCII_XON       0x11
  #define ASCII_XOFF      0x13

  #define FC_NONE         0x00
  #define FC_DTRDSR       0x01
  #define FC_RTSCTS       0x02
  #define FC_XONXOFF      0x04
  
  int speedValue[] = { 19200, 100, 300, 600, 1200, 2400, 4800,
    9600, 14400, 19200, 38400, 56000, 57600, 115200, 125000, 128000, 256000};
  // added 125000

  int parityValue[] = { NOPARITY, NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY};
  int databitsValue[] = { 8, 5, 6, 7, 8};
  int stopbitsValue[] = { ONESTOPBIT, ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS};
  int flowControlValue[] = { 0, 0, FC_DTRDSR, FC_RTSCTS, FC_XONXOFF, FC_DTRECTSD};

#endif

void JCOMObj::reset() {
  handle = -1;
  connected = false;
}

void JCOMObj::closeHandle() {
  if (handle == -1) return;
#if defined(WIN32)
  SetCommMask((HANDLE)handle, 0);
  EscapeCommFunction((HANDLE)handle, CLRDTR);
  PurgeComm((HANDLE)handle,
    PURGE_TXABORT | PURGE_RXABORT |
    PURGE_TXCLEAR | PURGE_RXCLEAR);
  CloseHandle((HANDLE)handle);
  handle = -1;
#endif
}

void JCOMObj::close() {
  if (!connected) return;
  connected = false;
  closeHandle();
  repaint();
}

void JCOMObj::open() {
  if (connected) return;
#if defined(WIN32)
  JString szPort = JString(typeTag2[type])+JInteger::toJString(port);
  handle = (int)CreateFile(
    szPort,
    GENERIC_READ | GENERIC_WRITE,
    0,                    // exclusive access
    NULL,                 // no security attrs
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    NULL);
  if (handle == -1) return;
  DCB dcb;
  COMMTIMEOUTS  CommTimeOuts;
  int FLOWCTRL = flowControlValue[flowControl];
  bufferSize = speedValue[speed]*2/3;
  SetCommMask((HANDLE)handle, EV_RXCHAR);
  SetupComm((HANDLE)handle, bufferSize, bufferSize);
  PurgeComm((HANDLE)handle,
    PURGE_TXABORT | PURGE_RXABORT |
    PURGE_TXCLEAR | PURGE_RXCLEAR);
/* 
  160  ms (F,0,0)
  291  ms (F,0,10)
  1082 ms (F,11,10)
  1100 ms (0,0,0)
  1160 ms (0,F,0)
  2200 ms (F,F,80)
*/
  CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
  CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
  CommTimeOuts.ReadTotalTimeoutConstant = 10;
  CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
  CommTimeOuts.WriteTotalTimeoutConstant = 1000;
  SetCommTimeouts((HANDLE)handle, &CommTimeOuts);
  dcb.DCBlength = sizeof(DCB);
  GetCommState((HANDLE)handle, &dcb);
  dcb.BaudRate = speedValue[speed];
  dcb.Parity = (BYTE)parityValue[parity];
  dcb.ByteSize = (BYTE)databitsValue[databits];
  dcb.StopBits = (BYTE)stopbitsValue[stopbits];
  dcb.fOutxDsrFlow = ((FLOWCTRL & FC_DTRDSR) != 0);
  dcb.fOutxCtsFlow = ((FLOWCTRL & FC_RTSCTS) != 0);
  dcb.fInX = dcb.fOutX = ((FLOWCTRL & FC_XONXOFF) != 0);
  if (FLOWCTRL == FC_DTRECTSD) {
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
  } else {
    dcb.fDtrControl = (dcb.fOutxDsrFlow) ?
      DTR_CONTROL_HANDSHAKE :
      DTR_CONTROL_ENABLE;
    dcb.fRtsControl = (dcb.fOutxCtsFlow) ?
      RTS_CONTROL_HANDSHAKE :
      RTS_CONTROL_ENABLE;
  }
  dcb.XonChar = ASCII_XON;
  dcb.XoffChar = ASCII_XOFF;
  dcb.XonLim = 100;
  dcb.XoffLim = 100;
  dcb.fBinary = true;
  dcb.fParity = true;
  if (SetCommState((HANDLE)handle, &dcb)) {
    connected = true;
    EscapeCommFunction((HANDLE)handle, SETDTR);
    if (!inputSet(SAMPLING).last()) {
      thread = JThread(this);
      thread.start();
      thread.setPriority(JThread::TNORM_PRIORITY+1);
    }
    repaint();
    return;
  }
  CloseHandle((HANDLE)handle);
#endif
}

void JCOMObj::engine(int n, JLinkObj& link) {
  if (n == INPUT) {
    if (connected) {
#if defined(WIN32)
      DWORD nLength;
      JBlock block;
      link.access(JBlockData(block));
      WriteFile((HANDLE)handle, (char*)block,
        block.size(), &nLength, null);
#endif
    }
    return;
  } else if (n == ENABLED) {
    link.access(JIntegerData(enabled));
    if (enabled) open();
    else close();
  } else if (n == SAMPLING) {
    link.access(JIntegerData(samplingClock));
    if (connected && samplingClock) {
#if defined(WIN32)

/* BenchMark Procedure
      int count = 200;
      int success = 0;
      DWORD nLength;
      int time = JSystem::currentTimeMillis();
      for (int i=0; i<count; i++) {
        JBlock block(1, 0);
        WriteFile((HANDLE)handle, (char*)block,
          block.size(), &nLength, null);
        if (ReadFile((HANDLE)handle, (char*)data,
          1, &nLength, null)) {
          success++;
        }
      }
      time = JSystem::currentTimeMillis()-time;
      JComponent::debug(JInteger::toJString(time)+" ms, success = "+
        JInteger::toJString(success));
*/

      DWORD nLength;
      COMSTAT ComStat ;
      DWORD dwErrorFlags;
      if (ClearCommError((HANDLE)handle, 
        &dwErrorFlags, &ComStat) && 
        (ComStat.cbInQue > 0)) {
        data = JBlock(ComStat.cbInQue, 0);
        if (ReadFile((HANDLE)handle, (char*)data,
          ComStat.cbInQue, &nLength, null)) {
          data.setSize(nLength);
          broadcast(0);
        }
      }
#endif
    }
  }
}

void JCOMObj::run() {
#if defined(WIN32)
  DWORD nLength;
  COMSTAT ComStat ;
  DWORD dwErrorFlags;
  DWORD dwLimit = bufferSize*4/5;
  while (connected) {
    do {
      if (!ClearCommError((HANDLE)handle, 
	&dwErrorFlags, &ComStat)) break;
      JThread::sleep(50);
    } while (connected && !ComStat.cbInQue);
    if (!connected || !ComStat.cbInQue) break;
    if (ComStat.cbInQue > dwLimit) break;
    data = JBlock(ComStat.cbInQue, 0);
    if (ReadFile((HANDLE)handle, (char*)data,
      ComStat.cbInQue, &nLength, null)) {
      data.setSize(nLength);
      broadcast(0);
    }
  }
  if (connected) {
    connected = false;
    closeHandle();
    repaint();
  }
#endif
}

JArray JCOMObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("type", type, typeTag));
  properties.append(JIntegerProperty("port", port, MIN_COM_PORT, MAX_COM_PORT));
  properties.append(JIntegerListProperty("speed", speed, speedTag));
  properties.append(JIntegerListProperty("parity", parity, parityTag));
  properties.append(JIntegerListProperty("databits", databits, databitsTag));
  properties.append(JIntegerListProperty("stopbits", stopbits, stopbitsTag));
  properties.append(JIntegerListProperty("flowControl", flowControl, flowControlTag));
  return properties;
}

boolean JCOMObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  boolean changed = false;
  boolean oldenabled = enabled;
  close();
  if (prop.getName() == JString("type")) {
    type = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("port")) {
    port = ((JIntegerProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("speed")) {
    speed = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("parity")) {
    parity = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("databits")) {
    databits = ((JIntegerListProperty*)&prop)->value;
    if ((stopbits > b_One) && (databits == d_Five)) {
      JMessageBox::create("DataBits must > 5 when StopBits > 1.",
	JMessageBox::BTN_OK);
      databits = ((JIntegerListProperty*)&prop)->value = 0;
    }
    changed = true;
  } else if (prop.getName() == JString("stopbits")) {
    stopbits = ((JIntegerListProperty*)&prop)->value;
    if ((stopbits > b_One) && (databits == d_Five)) {
      JMessageBox::create("StopBits must be 1 when DataBits is 5.",
	JMessageBox::BTN_OK);
      stopbits = ((JIntegerListProperty*)&prop)->value = 0;
    }
    changed = true;
  } else if (prop.getName() == JString("flowControl")) {
    flowControl = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  }
  if (enabled) open();
  if (changed) repaint();
  return changed;
}

void JCOMObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JCOMObj(1));
  addModuleButton(panel, JCOMObj(2));
  addModuleButton(panel, JCOMObj(3));
  addModuleButton(panel, JCOMObj(4));
}
