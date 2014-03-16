#include "JWaveInObj.h"
#include "JLinkObj.h"
#include "JBlock.h"
#include "JWaveData.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"
#include "JComponent.h"
#include "JSystem.h"
#include "JWindow.hpp"

char* theJWaveInObj = JWaveInObj(0).Register();

#if defined(WIN32)

  int JWaveInObj::getNumDevs() 
  { return waveInGetNumDevs()+1;}

#else

  int JWaveInObj::getNumDevs() 
  { return 1;}

#endif

const char* JWaveInObj::className() const { return "JWaveInObj";}
JObject* JWaveInObj::clone() const { return new JWaveInObj(*this);}

boolean JWaveInObj::check() {
#if defined(WIN32)
  MMRESULT rc;
  WAVEINCAPS wic;
  if (id == 0) wid = WAVE_MAPPER;
  else wid = id-1;
  rc = waveInGetDevCaps(wid, &wic, sizeof(wic));
  if (rc == MMSYSERR_NOERROR) {
    name = JString(wic.szPname, JString::needCopy);
    return (wic.dwFormats & formatValue[fid]) > 0;
  }
#endif
  return false;
}

JWaveInObj::JWaveInObj() {}

JWaveInObj::JWaveInObj(int _wid, int _fid) { 
  igm = 1;
  ogm = 2;
  id = _wid;
  fid = _fid;
  connected = false;
  pause = false;
  handle = null;
  delta = current = top = 0;
  blockSize = 32768;
  bufferSize = 8;
  valid = check();
}

JWaveInObj::~JWaveInObj() { close();}

void JWaveInObj::draw(JGraphics g, int x, int y, int w, int h) {
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
  drawText(g, "Input", rect2);
  drawText(g, name, rect3);
}

void JWaveInObj::access(int n, JLinkObj& link, const JDataType& _data) {
  if (!n) _data.assign(data);
  else INT(_data) = value;
}

JString JWaveInObj::inputTag(int n) { return "enable(logical)";}
int JWaveInObj::inputType(int n) 
{ return JIntegerData::id;}
int JWaveInObj::outputType(int n) 
{ return (!n) ? JWaveData::id : JIntegerData::id;}
JString JWaveInObj::outputTag(int n) {
  char* tag[] = { "output", "counter"};
  return tag[n];
}
JFRect JWaveInObj::inputArea(int n) 
{ return topArea(n, 0, 1);}
JFRect JWaveInObj::outputArea(int n) { 
  if (!n) return rightArea(n, 0, 1);
  return bottomArea(n, 1, 1);
}
int JWaveInObj::inputFace(int n) { return TOP;}
int JWaveInObj::outputFace(int n) 
{ return (!n) ? RIGHT : BOTTOM;}
JFPoint JWaveInObj::inputPoint(int n, JLinkObj& link) 
{ return topPoint(n, link, 0, 1);}
JFPoint JWaveInObj::outputPoint(int n, JLinkObj& link) { 
  if (!n) return rightPoint(n, link, 0, 1);
  return bottomPoint(n, link, 1, 1);
}

boolean JWaveInObj::dataNotify(JEvent& e, void* pdata) {
#if defined(WIN32)
  cs.lock();
  MMRESULT rc;
  WAVEHDR *whdr;
  if (!connected || !block.size()) goto CSEND;
  data = *(JBlock*)block[current];
  if (data != pdata) goto CSEND;
  whdr = (WAVEHDR*)(char*)data;
  whdr->dwFlags = null;
  value += whdr->dwBytesRecorded;
  broadcast(1);
  data.Dereference();
  whdr->dwUser = MAKELONG(NORM_BLOCK, fid);
  rc = waveInUnprepareHeader((HWAVEIN)handle, 
    whdr, sizeof(WAVEHDR));
  rc = waveInPrepareHeader((HWAVEIN)handle, 
    whdr, sizeof(WAVEHDR));
  rc = waveInAddBuffer((HWAVEIN)handle,
    whdr, sizeof(WAVEHDR));
  if (JSystem::currentTimeMillis()-timeBase < 800) {
    broadcast(0);
    timeBase += msPerBlock;
  } else timeBase = JSystem::currentTimeMillis();
  current = ((current+1) % bufferSize);
CSEND:
  cs.unlock();
#endif
  return true;
}

void JWaveInObj::close() {
  int i;
  int next, done, ndone;
  cs.lock();
  if (!connected) goto CSEND;
  connected = false;
#if defined(WIN32)
  WAVEHDR *whdr, *nwhdr;
  waveInStop((HWAVEIN)handle);
  waveInReset((HWAVEIN)handle);
  whdr = (WAVEHDR*)(char*)*(JBlock*)block[current];
  done = (whdr->dwFlags & WHDR_DONE) && 
    (whdr->dwBytesRecorded != 0);
  for (;; whdr=nwhdr, current=next, done=ndone) {
    next = ((current+1) % bufferSize);
    nwhdr = (WAVEHDR*)(char*)*(JBlock*)block[next];
    ndone = (nwhdr->dwFlags & WHDR_DONE) && 
      (nwhdr->dwBytesRecorded != 0);
    if (done) {
      if (!ndone) whdr->dwUser = MAKELONG(
	whdr->dwUser | TAIL_BLOCK, fid);
      data = *(JBlock*)block[current];
      data.Dereference();
      value += whdr->dwBytesRecorded;
      whdr->dwBytesRecorded = null;
      broadcast(0);
      broadcast(1);
    } else break;
  }
  for (i=block.size(); i-->0;) {
    whdr = (WAVEHDR*)(char*)*(JBlock*)block[i];
    waveInUnprepareHeader((HWAVEIN)handle, 
      whdr, sizeof(WAVEHDR));
  }
  waveInClose((HWAVEIN)handle);
#endif
  handle = null;
  block.delAll();
  repaint();
CSEND:
  cs.unlock();
}

#if defined(WIN32)
void CALLBACK waveInProc(int hwo, uint uMsg, 
  long dwInstance, long dwParam1, long dwParam2) {
  if (uMsg == WIM_DATA) {
    PostMessage((HWND)(int)*(JComponent*)
      (((JViewObj*)dwInstance)->parent->getRoot()), 
      UM_DATA, dwInstance, dwParam1);
  }
}
#endif

void JWaveInObj::open() {
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
  rc = waveInOpen(
    (LPHWAVEIN)&handle, wid, &wfx, 
    (DWORD)(void*)waveInProc,
    (DWORD)this, CALLBACK_FUNCTION);
  if ((rc == MMSYSERR_NOERROR) && handle) {
    int i, size = sizeof(WAVEHDR)+blockSize;
    connected = true;
    value = current = 0;
    repaint();
    broadcast(1);
    block.delAll();
    for (i=0; i<bufferSize; i++) {
      block.append(JBlock(size, 0));
      WAVEHDR *whdr = (WAVEHDR*)(char*)*(JBlock*)block[i];
      if (whdr) {
        whdr->lpData = (LPSTR)(whdr+1);
        whdr->dwBufferLength = blockSize;
	whdr->dwFlags = null;
	whdr->dwUser = MAKELONG(
	  ((i==0) ? HEAD_BLOCK : NORM_BLOCK), fid); 
	rc = waveInPrepareHeader(
	  (HWAVEIN)handle,
	  whdr, sizeof(WAVEHDR));
	if (rc == MMSYSERR_NOERROR) {
	  rc = waveInAddBuffer(
	    (HWAVEIN)handle,
	    whdr, sizeof(WAVEHDR));
	}
	if (rc != MMSYSERR_NOERROR) break;
      } else {
	rc = MMSYSERR_NOERROR+1;
	break;
      }
    }
    if (rc == MMSYSERR_NOERROR)
      rc = waveInStart((HWAVEIN)handle);
    if (rc != MMSYSERR_NOERROR) close();
    timeBase = JSystem::currentTimeMillis();
  }

#endif
CSEND:
  cs.unlock();
}

void JWaveInObj::engine(int n, JLinkObj& link) {
  int oEnabled = enabled;
  link.access(JIntegerData(enabled));
  enabled = (enabled != 0);
  if (oEnabled != enabled) {
    if (enabled && !connected) open();
    else if (!enabled && connected) close();
  }
}

JArray JWaveInObj::getDeviceTag() {
  JArray deviceTag;
#if defined(WIN32)
  MMRESULT rc;
  WAVEINCAPS wic;
  int nMaxDevices = getNumDevs(), tid;
  for (int i=0; i<nMaxDevices; i++) {
    if (i == 0) tid = WAVE_MAPPER;
    else tid = i-1;
    rc = waveInGetDevCaps(tid, &wic, sizeof(wic));
    if (rc == MMSYSERR_NOERROR)
      deviceTag.append(JString(wic.szPname, JString::needCopy));
  }
#endif
  return deviceTag;
}

void JWaveInObj::addButton(JComponent* panel) { 
  int numDevs = getNumDevs();
  for (int i=0; i<numDevs; i++)
    addModuleButton(panel, JWaveInObj(i));
}
