#include "JWaveOutObj.h"
#include "JLinkObj.h"
#include "JBlock.h"
#include "JWaveData.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JComponent.h"
#include "JWindow.hpp"

char* theJWaveOutObj = JWaveOutObj(0).Register();
int JWaveOutObj::msPerBlock = 160;
char* JWaveOutObj::formatTag[] = {
  "11.025kHz/mono/8bit",
  "11.025kHz/stereo/8bit",
  "11.025kHz/mono/16bit",
  "11.025kHz/stereo/16bit",
  "22.05kHz/mono/8bit",
  "22.05kHz/stereo/8bit",
  "22.05kHz/mono/16bit",
  "22.05kHz/stereo/16bit",
  "44.1kHz/mono/8bit",
  "44.1kHz/stereo/8bit",
  "44.1kHz/mono/16bit",
  "44.1Hz/stereo/16bit",
  "8kHz/mono/8bit",
  "8kHz/stereo/8bit",
  "8kHz/mono/16bit",
  "8kHz/stereo/16bit",
  null};

int JWaveOutObj::frequencyValue[] = 
  { 11025, 11025, 11025, 11025, 
    22050, 22050, 22050, 22050, 
    44100, 44100, 44100, 44100,
    8000, 8000, 8000, 8000};
int JWaveOutObj::channelValue[] = 
  { 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2};
int JWaveOutObj::bitsValue[] = 
  { 8, 8, 16, 16, 8, 8, 16, 16, 8, 8, 16, 16, 8, 8, 16, 16};

#if defined(WIN32)

  int JWaveOutObj::formatValue[] = {
    WAVE_FORMAT_1M08, 
    WAVE_FORMAT_1S08, 
    WAVE_FORMAT_1M16, 
    WAVE_FORMAT_1S16, 
    WAVE_FORMAT_2M08, 
    WAVE_FORMAT_2S08,
    WAVE_FORMAT_2M16, 
    WAVE_FORMAT_2S16, 
    WAVE_FORMAT_4M08, 
    WAVE_FORMAT_4S08, 
    WAVE_FORMAT_4M16, 
    WAVE_FORMAT_4S16,
    WAVE_FORMAT_1M08, 
    WAVE_FORMAT_1S08, 
    WAVE_FORMAT_1M16, 
    WAVE_FORMAT_1S16, 
  };

  int JWaveOutObj::getNumDevs() 
  { return waveOutGetNumDevs()+1;}

#else

  int JWaveOutObj::formatValue[] = { null};
  int JWaveOutObj::getNumDevs() { return 1;}

#endif

void JWaveOutObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "wid", id);
  putInteger(os, "fid", fid);
  putInteger(os, "bufferSize", bufferSize);
}

void JWaveOutObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  id = getInteger(dict, "wid");
  fid = getInteger(dict, "fid");
  bufferSize = getInteger(dict, "bufferSize");
  bufferSize = max(6, min(20, bufferSize));
  valid = check();
}

const char* JWaveOutObj::className() const { return "JWaveOutObj";}
JObject* JWaveOutObj::clone() const { return new JWaveOutObj(*this);}

boolean JWaveOutObj::check() {
#if defined(WIN32)
  MMRESULT rc;
  WAVEOUTCAPS woc;
  if (id == 0) wid = WAVE_MAPPER;
  else wid = id-1;
  rc = waveOutGetDevCaps(wid, &woc, sizeof(woc));
  if (rc == MMSYSERR_NOERROR) {
    name = JString(woc.szPname, JString::needCopy);
    return (woc.dwFormats & formatValue[fid]) > 0;
  }
#endif
  return false;
}

JWaveOutObj::JWaveOutObj() {}
JWaveOutObj::JWaveOutObj(int _wid, int _fid) { 
  igm = 2;
  ogm = OUT_LAST;
  id = _wid;
  fid = _fid;
  connected = false;
  pause = false;
  handle = null;
  delta = current = top = 0;
  blockSize = 32768;
  bufferSize = 10;
  feedback = NORMAL;
  valid = check();
}

JWaveOutObj::~JWaveOutObj() { close();}

void JWaveOutObj::paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale) {
  JAddObj::paint(g, dx, dy, rgn, scale);
  JRect rect = getIExtent(dx, dy, scale);
  int kw = depth2*3;
  if ((rect.width > kw) && (rect.height > kw)) {
    if (connected) g.setJColor(JColor::red);
    else g.setJColor(JColor::red.darker());
    g.fillRect(rect.x+depth2, rect.y+depth2, depth2, depth2);
  }
}

void JWaveOutObj::draw(JGraphics g, int x, int y, int w, int h) {
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
  drawText(g, "Wave", rect1);
  drawText(g, "Output", rect2);
  drawText(g, name, rect3);
}

void JWaveOutObj::access(int n, JLinkObj& link, const JDataType& _data) { 
  switch (n) {
    case OUT_COUNTER:
      INT(_data) = value;
      break;
    case OUT_DELTA:
      INT(_data) = delta;
      break;
    case OUT_FEEDBACK:
      INT(_data) = feedback;
      break;
  }
}

int JWaveOutObj::inputType(int n) 
{ return (!n) ? JWaveData::id : JIntegerData::id;}
boolean JWaveOutObj::inputAllowed(int n) 
{ return (boolean)(!inputSet(n).last());}
JString JWaveOutObj::outputTag(int n) { 
  char* tag[] = {"counter", "delta", "waveFeedback"};
  return tag[n];
}
JFRect JWaveOutObj::outputArea(int n) 
{ return bottomArea(n, 0, OUT_LAST);}
int JWaveOutObj::outputFace(int n) { return BOTTOM;}
JFPoint JWaveOutObj::outputPoint(int n, JLinkObj& link) 
{ return bottomPoint(n, link, 0, OUT_LAST);}

void JWaveOutObj::reset() {
  handle = null;
  connected = false;
}

boolean JWaveOutObj::dataNotify(JEvent& e, void* pdata) {
#if defined(WIN32)
  cs.lock();
  WAVEHDR *whdr;
  JBlock data;
  if (!connected || !block.size()) goto CSEND;
  data = *(JBlock*)block[current];
  if (data != pdata) goto CSEND;
  whdr = (WAVEHDR*)(char*)data;
  value += whdr->dwBytesRecorded;
  if (whdr->dwUser & TAIL_BLOCK) value = 0;
  broadcast(OUT_COUNTER);
  waveOutUnprepareHeader(
    (HWAVEOUT)handle,
    whdr, sizeof(WAVEHDR));
  current = (current+1) % bufferSize;
  if (!pause && (current == top)) {
    MMRESULT rc = waveOutPause((HWAVEOUT)handle);
    if (rc == MMSYSERR_NOERROR) {
      feedback = PAUSE;
      broadcast(OUT_FEEDBACK);
      pause = true;
    }
  }
  delta = (top+bufferSize-current)%bufferSize;
  broadcast(OUT_DELTA);
CSEND:
  cs.unlock();
#endif
  return true;
}

void JWaveOutObj::close() {
  cs.lock();
  if (!connected) goto CSEND;
  connected = false;
#if defined(WIN32)
  waveOutPause((HWAVEOUT)handle);
  waveOutReset((HWAVEOUT)handle);
  while (current != top) {
    WAVEHDR *whdr = (WAVEHDR*)(char*)
      *(JBlock*)block[current];
    waveOutUnprepareHeader((HWAVEOUT)handle, 
      whdr, sizeof(WAVEHDR));
    current = (current+1) % bufferSize;
    delta = (top+bufferSize-current)%bufferSize;
    broadcast(OUT_DELTA);
  }
  waveOutClose((HWAVEOUT)handle);
#endif
  handle = null;
  block.delAll();
  feedback = NORMAL;
  broadcast(OUT_FEEDBACK);
  repaint();
CSEND:
  cs.unlock();
}

#if defined(WIN32)
void CALLBACK waveOutProc(int hwo, uint uMsg, 
  long dwInstance, long dwParam1, long dwParam2) {
  if (uMsg == WOM_DONE) {
    PostMessage((HWND)(int)*(JComponent*)
      (((JViewObj*)dwInstance)->parent->getRoot()), 
      UM_DATA, dwInstance, dwParam1);
  }
}
#endif

void JWaveOutObj::open() {
  cs.lock();
  if (connected) goto CSEND;
#if defined(WIN32)
  MMRESULT rc;
  WAVEFORMATEX wfx;
  wfx.wFormatTag = WAVE_FORMAT_PCM;
  wfx.nChannels = channelValue[fid];
  wfx.nSamplesPerSec = frequencyValue[fid];
  wfx.wBitsPerSample = bitsValue[fid];
  wfx.nBlockAlign = wfx.nChannels*wfx.wBitsPerSample/8;
  wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
  wfx.cbSize = 0;
  blockSize = (wfx.nAvgBytesPerSec*msPerBlock/1000);
  rc = waveOutOpen(
    (LPHWAVEOUT)&handle, wid, &wfx, 
    (DWORD)(void*)waveOutProc,
    (DWORD)this, CALLBACK_FUNCTION);
  if ((rc == MMSYSERR_NOERROR) && handle) {
    int i, size = sizeof(WAVEHDR)+blockSize;
    block.delAll();
    for (i=0; i<bufferSize; i++)
      block.append(JBlock());
    connected = true;
    pause = false;
    delta = value = current = top = 0;
    repaint();
    broadcast(OUT_COUNTER);
    broadcast(OUT_DELTA);
    if (rc == MMSYSERR_NOERROR) {
      DWORD dwVol;
      rc = waveOutGetVolume(
	(HWAVEOUT)handle, &dwVol);
      if (rc == MMSYSERR_NOERROR) {
        if ((LOWORD(dwVol) < 0x8080) ||
          ((wfx.nChannels == 2) && 
	  (HIWORD(dwVol) < 0x8080))) {
          rc = waveOutSetVolume(
	    (HWAVEOUT)handle, 
	    (DWORD)MAKELONG(0x8080, 0x8080));
	}
      }
    }
    if (rc == MMSYSERR_NOERROR) {
      WAVEOUTCAPS woc;
      rc = waveOutGetDevCaps(wid, &woc, sizeof(woc));
      if (woc.dwSupport & WAVECAPS_PLAYBACKRATE) {
	DWORD dwRate;
        rc = waveOutGetPlaybackRate((HWAVEOUT)handle, &dwRate);
        rc = waveOutSetPlaybackRate((HWAVEOUT)handle, MAKELONG(HIWORD(dwRate)*2, LOWORD(dwRate)));
      }
      if (woc.dwSupport & WAVECAPS_PITCH) {
	DWORD dwPitch;
        rc = waveOutGetPitch((HWAVEOUT)handle, &dwPitch);
        rc = waveOutSetPitch((HWAVEOUT)handle, MAKELONG( HIWORD(dwPitch)*2, LOWORD(dwPitch)));
      }
    }
    connected++;
    if (rc != MMSYSERR_NOERROR) close();
    rc = waveOutPause((HWAVEOUT)handle);
    if (rc == MMSYSERR_NOERROR) {
      pause = true;
      feedback = PAUSE;
      broadcast(OUT_FEEDBACK);
    }
  }
#endif
CSEND:;
  cs.unlock();
}

void JWaveOutObj::engine(int n, JLinkObj& link) {
  if (!n) {
#if defined(WIN32)
    int nid;
    JBlock data;
    link.access(JBlockData(data));
    if (data.size() < sizeof(WAVEHDR)) return;
    cs.lock();
    data.Dereference();
    MMRESULT rc;
    WAVEHDR *whdr = (WAVEHDR*)(char*)data;
    nid = max(0, min(_LAST-1, 
      HIWORD(whdr->dwUser)));
    if ((nid != fid) || (whdr->dwUser & HEAD_BLOCK)) {
      fid = nid;
      if (connected > true) {
        close();
        open();
        if (!connected) goto CSEND;
      } else repaint();
    }
    if (connected > true) {
      delta = ((top-current+bufferSize)%bufferSize);
      if (delta == bufferSize-1) {
        feedback = OVERFLOW;
        broadcast(OUT_FEEDBACK);
        goto CSEND;
      }
      block.set(top, data);
      whdr = (WAVEHDR*)(char*)*(JBlock*)block[top];
      if (!whdr) {
	close();
	goto CSEND;
      }
      whdr->lpData = (LPSTR)(whdr+1);
      whdr->dwBufferLength = whdr->dwBytesRecorded;
      whdr->dwFlags = null;
      rc = waveOutPrepareHeader(
       (HWAVEOUT)handle,
       whdr, sizeof(WAVEHDR));
      if (rc == MMSYSERR_NOERROR) {
	rc = waveOutWrite(
	  (HWAVEOUT)handle,
	  whdr, sizeof(WAVEHDR));
      }
      if (pause && ((whdr->dwUser & TAIL_BLOCK) ||
	(top != current) && (delta >= (bufferSize/2-1)))) {
        waveOutRestart((HWAVEOUT)handle);
	pause = false;
        feedback = NORMAL;
        broadcast(OUT_FEEDBACK);
      }
      top = ((top+1) % bufferSize);
      delta++;
      broadcast(OUT_DELTA);
    }
  CSEND:
    cs.unlock();
#endif
  } else {
    int oEnabled = enabled;
    link.access(JIntegerData(enabled));
    enabled = (enabled != 0);
    if (oEnabled != enabled) {
      if (enabled && !connected) open();
      else if (!enabled && connected) close();
    }
  }
}

JArray JWaveOutObj::getDeviceTag() {
  JArray deviceTag;
#if defined(WIN32)
  MMRESULT rc;
  WAVEOUTCAPS woc;
  int nMaxDevices = getNumDevs(), tid;
  for (int i=0; i<nMaxDevices; i++) {
    if (i == 0) tid = WAVE_MAPPER;
    else tid = i-1;
    rc = waveOutGetDevCaps(tid, &woc, sizeof(woc));
    if (rc == MMSYSERR_NOERROR)
      deviceTag.append(JString(woc.szPname, JString::needCopy));
  }
#endif
  return deviceTag;
}

JArray JWaveOutObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JIntegerListProperty("device", id, getDeviceTag()));
  properties.append(JIntegerListProperty("format", fid, formatTag));
  properties.append(JIntegerProperty("bufferSize", bufferSize, 6, 20));
  return properties;
}

boolean JWaveOutObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  boolean changed = false;
  boolean oldenabled = enabled;
  close();
  if (prop.getName() == JString("device")) {
    id = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("format")) {
    fid = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  } else if (prop.getName() == JString("bufferSize")) {
    bufferSize = ((JIntegerListProperty*)&prop)->value;
    changed = true;
  }
  if (changed) {
    valid = check();
    if (oldenabled) open();
    repaint();
    return true;
  }
  return false;
}

void JWaveOutObj::addButton(JComponent* panel) { 
  int numDevs = getNumDevs();
  for (int i=0; i<numDevs; i++)
    addModuleButton(panel, JWaveOutObj(i));
}

