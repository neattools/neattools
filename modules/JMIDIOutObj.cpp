#include "JMIDIOutObj.h"
#include "JLinkObj.h"
#include "JThread.h"
#include "JInteger.h"
#include "JMIDIData.h"
#include "JIntegerListProperty.h"
#include "JWindow.hpp"

char* theJMIDIOutObj = JMIDIOutObj(0).Register();

#if defined(WIN32)

  int JMIDIOutObj::getNumDevs() 
  { return midiOutGetNumDevs()+1;}

#else

  int JMIDIOutObj::getNumDevs() 
  { return 1;}

#endif

void JMIDIOutObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "id", id);
}

void JMIDIOutObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  id = getInteger(dict, "id");
  valid = check();
}

const char* JMIDIOutObj::className() const { return "JMIDIOutObj";}
JObject* JMIDIOutObj::clone() const { return new JMIDIOutObj(*this);}

boolean JMIDIOutObj::check() {
#if defined(WIN32)
  MMRESULT rc;
  MIDIOUTCAPS moc;
  if (id == 0) mid = MIDI_MAPPER;
  else mid = id-1;
  rc = midiOutGetDevCaps(mid,
    &moc, sizeof(moc));
  if (rc == MMSYSERR_NOERROR) {
    name = moc.szPname;
    name.Dereference();
    hasPatchCaching = (moc.dwSupport & MIDICAPS_CACHE) != 0;
    return true;
  } else name = EMPTY;
#endif
  return false;
}

JMIDIOutObj::JMIDIOutObj() {}
JMIDIOutObj::JMIDIOutObj(int _id) { 
  id = _id;
  connected = false;
  enabled = false;
  hasPatchCaching = false;
  igm = 2;
  ogm = 0;
  handle = -1;
  valid = check();
}

JMIDIOutObj::~JMIDIOutObj() { close();}

void JMIDIOutObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JMIDIOutObj::draw(JGraphics g, int x, int y, int w, int h) {
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
  drawText(g, "Output", rect2);
  drawText(g, name, rect3);
}

int JMIDIOutObj::inputType(int n) 
{ return (!n) ? JMIDIData::id : JIntegerData::id;}
boolean JMIDIOutObj::inputAllowed(int n) 
{ return (boolean)((!n) ? true : !inputSet(n).last());}

void JMIDIOutObj::reset() {
  handle = -1;
  connected = false;
}

void JMIDIOutObj::close() {
  cs.lock();
  if (!connected) goto CSEND;
  connected = false;
#if defined(WIN32)
  midiOutReset((HMIDIOUT)handle);
  midiOutClose((HMIDIOUT)handle);
#endif
  handle = -1;
  repaint();
CSEND:
  cs.unlock();
}

void JMIDIOutObj::open() {
  cs.lock();
#if defined(WIN32)
  MMRESULT rc;
  if (connected) goto CSEND;
  rc = midiOutOpen(
    (LPHMIDIOUT)&handle,
    mid, null, null, CALLBACK_NULL);
  if (rc == MMSYSERR_NOERROR) {
    connected = true;
    repaint();
  }
#endif
CSEND:;
  cs.unlock();
}

void JMIDIOutObj::engine(int n, JLinkObj& link) {
  if (!n) {
    cs.lock();
    if (connected) {
#if defined(WIN32)
      int ivalue;
      link.access(JIntegerData(ivalue));
      midiOutShortMsg((HMIDIOUT)handle, (DWORD)ivalue);
#endif
    }
    cs.unlock();
  } else {
    link.access(JIntegerData(enabled));
    if (enabled && !connected) open();
    else if (!enabled && connected) close();
  }
}

JArray JMIDIOutObj::getDeviceTag() {
  JArray deviceTag;
#if defined(WIN32)
  MMRESULT rc;
  MIDIOUTCAPS moc;
  int nMaxDevices = getNumDevs(), tid;
  for (int i=0; i<nMaxDevices; i++) {
    if (i == 0) tid = MIDI_MAPPER;
    else tid = i-1;
    rc = midiOutGetDevCaps(tid, &moc, sizeof(moc));
    if (rc == MMSYSERR_NOERROR)
      deviceTag.append(JString(moc.szPname, JString::needCopy));
  }
#endif
  return deviceTag;
}

JArray JMIDIOutObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("device", id, getDeviceTag()));
  return properties;
}

boolean JMIDIOutObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("device")) {
    boolean oldenabled = enabled;
    close();
    id = ((JIntegerListProperty*)&prop)->value;
    valid = check();
    if (oldenabled) open();
    repaint();
    return true;
  }
  return false;
}

void JMIDIOutObj::addButton(JComponent* panel) { 
  int numDevs = getNumDevs();
  for (int i=0; i<numDevs; i++)
    addModuleButton(panel, JMIDIOutObj(i));
}
