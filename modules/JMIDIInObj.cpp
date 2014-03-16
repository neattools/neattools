#include "JMIDIInObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JMIDIData.h"
#include "JIntegerListProperty.h"
#include "JComponent.h"
#include "JWindow.hpp"
#include <memory.h>

char* theJMIDIInObj = JMIDIInObj(0).Register();

#if defined(WIN32)

  int JMIDIInObj::getNumDevs() 
  { return midiInGetNumDevs();}

#else

  int JMIDIInObj::getNumDevs() 
  { return 1;}

#endif

void JMIDIInObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "miscEvent", miscEvent);
  putInteger(os, "ctrlEvent", ctrlEvent);
}

void JMIDIInObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  miscEvent = getInteger(dict, "miscEvent");
  ctrlEvent = getInteger(dict, "ctrlEvent");
}

const char* JMIDIInObj::className() const { return "JMIDIInObj";}
JObject* JMIDIInObj::clone() const { return new JMIDIInObj(*this);}

boolean JMIDIInObj::check() {
#if defined(WIN32)
  MMRESULT rc;
  MIDIINCAPS mic;
  mid = id;
  rc = midiInGetDevCaps(mid,
    &mic, sizeof(mic));
  if (rc == MMSYSERR_NOERROR) {
    name = mic.szPname;
    name.Dereference();
    return true;
  } else name = EMPTY;
#endif
  return false;
}

JMIDIInObj::JMIDIInObj(int _id) { 
  id = _id;
  connected = false;
  enabled = false;
  miscEvent = false;
  ctrlEvent = false;
  igm = 1;
  ogm = 1;
  handle = -1;
  blockSize = 1024;
  valid = check();
}

JMIDIInObj::~JMIDIInObj() { close();}

void JMIDIInObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  drawText(g, "MIDI", rect1);
  drawText(g, "Input", rect2);
  drawText(g, name, rect3);
}

JString JMIDIInObj::inputTag(int n) { return "enable(logical)";}
int JMIDIInObj::inputType(int n) 
{ return JIntegerData::id;}
int JMIDIInObj::outputType(int n) 
{ return JMIDIData::id;}
boolean JMIDIInObj::inputAllowed(int n) 
{ return (boolean)(!inputSet(n).last());}
JFRect JMIDIInObj::inputArea(int n) 
{ return topArea(n, 0, 1);}
int JMIDIInObj::inputFace(int n) { return TOP;}
JFPoint JMIDIInObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, 1);}

boolean JMIDIInObj::dataNotify(JEvent& e, void* pdata) {
  value = (int)pdata;
  broadcast(0);
  return true;
}

boolean JMIDIInObj::auxNotify(JEvent& e, void* pdata) {
#if defined(WIN32)
  cs.lock();
  MMRESULT rc;
  MIDIHDR *mhdr;
  if (!connected) goto CSEND;
  mhdr = (MIDIHDR*)(char*)data;
  if ((void*)mhdr != pdata) goto CSEND;
  if (!(mhdr->dwFlags & MHDR_DONE)) goto CSEND;
  if (mhdr->dwBytesRecorded > 0) {}
  rc = midiInUnprepareHeader((HMIDIIN)handle, 
    mhdr, sizeof(MIDIHDR));
  if (rc == MMSYSERR_NOERROR)
    rc = midiInPrepareHeader((HMIDIIN)handle, 
      mhdr, sizeof(MIDIHDR));
  if (rc == MMSYSERR_NOERROR)
    rc = midiInAddBuffer((HMIDIIN)handle,
      mhdr, sizeof(MIDIHDR));
  if (rc != MMSYSERR_NOERROR) close();
#endif
  cs.unlock();
  return true;
CSEND:
  cs.unlock();
  return false;
}

void JMIDIInObj::close() {
  cs.lock();
  if (!connected) goto CSEND;
  connected = false;
#if defined(WIN32)
  midiInStop((HMIDIIN)handle);
  midiInReset((HMIDIIN)handle);
  midiInUnprepareHeader((HMIDIIN)handle, 
    (MIDIHDR*)(char*)data, sizeof(MIDIHDR));
  midiInClose((HMIDIIN)handle);
#endif
  handle = -1;
  data.Release();
  repaint();
CSEND:;
  cs.unlock();
}

#if defined(WIN32)
void CALLBACK midiInProc(int hwo, uint uMsg, 
  long dwInstance, long dwParam1, long dwParam2) {
  JMIDIInObj *obj = (JMIDIInObj*)dwInstance;
  if ((uMsg == MIM_DATA)) {
    switch ((*(uchar*)&dwParam1)>>4) {
      case 0xF: 
	if (!obj->miscEvent) return;
	break;
      case 0xB: 
	if (!obj->ctrlEvent) return;
	break;
    }
    PostMessage((HWND)(int)*(JComponent*)
      (obj->parent->getRoot()), 
      UM_DATA, dwInstance, dwParam1);
  } else if ((uMsg == MIM_LONGDATA)) {
    PostMessage((HWND)(int)*(JComponent*)
      (obj->parent->getRoot()), 
      UM_AUX, dwInstance, dwParam1);
  }
}
#endif

void JMIDIInObj::open() {
  cs.lock();
#if defined(WIN32)
  MMRESULT rc;
  if (connected) goto CSEND;
  rc = midiInOpen(
    (LPHMIDIIN)&handle, mid, 
    (DWORD)(void*)midiInProc,
    (DWORD)this, CALLBACK_FUNCTION);
  if (rc == MMSYSERR_NOERROR) {
    int size = sizeof(MIDIHDR)+blockSize;
    connected = true;
    repaint();
    rc = midiInReset((HMIDIIN)handle);
    if (rc == MMSYSERR_NOERROR) {
      data = JBlock(size, 0);
      MIDIHDR *mhdr = (MIDIHDR*)(char*)data;
      if (mhdr) {
        mhdr->lpData = (LPSTR)(mhdr+1);
        mhdr->dwBufferLength = blockSize;
        rc = midiInPrepareHeader((HMIDIIN)handle, 
          mhdr, sizeof(MIDIHDR));
	if (rc == MMSYSERR_NOERROR)
          rc = midiInAddBuffer((HMIDIIN)handle, 
            mhdr, sizeof(MIDIHDR));
	if (rc == MMSYSERR_NOERROR)
	  rc = midiInStart((HMIDIIN)handle);
      }
    }
  }
#endif
CSEND:;
  cs.unlock();
}

void JMIDIInObj::engine(int n, JLinkObj& link) {
  link.access(JIntegerData(enabled));
  if (enabled && !connected) open();
  else if (!enabled && connected) close();
}

JArray JMIDIInObj::getDeviceTag() {
  JArray deviceTag;
#if defined(WIN32)
  MMRESULT rc;
  MIDIINCAPS mic;
  int nMaxDevices = getNumDevs(), tid;
  for (int i=0; i<nMaxDevices; i++) {
    tid = i-1;
    rc = midiInGetDevCaps(tid, &mic, sizeof(mic));
    if (rc == MMSYSERR_NOERROR)
      deviceTag.append(JString(mic.szPname, JString::needCopy));
  }
#endif
  return deviceTag;
}

JArray JMIDIInObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("device", id, getDeviceTag()));
  properties.append(JIntegerListProperty("miscEvent", 
    miscEvent, JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("ctrlEvent", 
    ctrlEvent, JIntegerListProperty::booleanTag));
  return properties;
}

boolean JMIDIInObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("device")) {
    boolean oldenabled = enabled;
    close();
    id = ((JIntegerListProperty*)&prop)->value;
    valid = check();
    if (oldenabled) open();
    repaint();
    return true;
  } else if (prop.getName() == JString("miscEvent")) {
    miscEvent = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("ctrlEvent")) {
    ctrlEvent = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

void JMIDIInObj::addButton(JComponent* panel) { 
  int numDevs = getNumDevs();
  for (int i=0; i<numDevs; i++)
    addModuleButton(panel, JMIDIInObj(i));
}
