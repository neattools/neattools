#include "JWaveFileObj.h"
#include "JWaveOutObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JWaveData.h"
#include "JSystem.h"
#include "JFileProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JIOException.h"
#include "JEOFException.h"
#include "JWindow.hpp"

char* theJWaveFileObj = JWaveFileObj().Register();		   
const char* JWaveFileObj::className() const { return "JWaveFileObj";}
JObject* JWaveFileObj::clone() const { return new JWaveFileObj(*this);}

JWaveFileObj::JWaveFileObj() {
  id = -1;
  nBlockAlign = 1;
  type = "*.wav";
  filename = composit(prefix, sequence);
}

JWaveFileObj::~JWaveFileObj() { 
  close();
}

boolean JWaveFileObj::check(boolean redraw) {
  id = -1;
  startPos = 0;
  count = 0;
  total = 0;
#if defined(WIN32)
  try {
    fis.open(filename);
    int i, size, fmtSize;
    JBlock tag(4, 0);
    WAVEFORMATEX wfx;
    WAVEHDR *whdr;
    fis >> tag;
    if (JString(tag) != JString("RIFF")) goto ENDCHECK;
    fis >> JBlock(size);
    fis >> tag;
    if (JString(tag) != JString("WAVE")) goto ENDCHECK;
    fis >> tag;
    if (JString(tag) != JString("fmt ")) goto ENDCHECK;
    fis >> JBlock(fmtSize);
    fis >> JBlock(fmtSize, (char*)&wfx);
    if (wfx.wFormatTag != WAVE_FORMAT_PCM) goto ENDCHECK;
    for (i=0; i<JWaveOutObj::_LAST; i++) {
      if ((wfx.nChannels == JWaveOutObj::channelValue[i]) &&
	((int)wfx.nSamplesPerSec == JWaveOutObj::frequencyValue[i]) &&
	(wfx.wBitsPerSample == JWaveOutObj::bitsValue[i])) {
	id = i;
	break;
      }
    }
    if (id == -1) goto ENDCHECK;
    nBlockAlign = wfx.nBlockAlign = wfx.nChannels*wfx.wBitsPerSample/8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
    wfx.cbSize = 0;
    blockSize = (wfx.nAvgBytesPerSec*
      JWaveOutObj::msPerBlock/1000);
    for (;;) {
      fis >> tag;
      fis >> JBlock(total);
      if (JString(tag) == JString("data")) break;
      fis.move(total);
    }
    data = JBlock(sizeof(WAVEHDR)+blockSize, 0);
    whdr = (WAVEHDR*)(char*)data;
    if (whdr) {
      whdr->lpData = (LPSTR)(whdr+1);
      whdr->dwBufferLength = blockSize;
      whdr->dwBytesRecorded = blockSize;
      whdr->dwFlags = null;
      whdr->dwUser = MAKELONG(JWaveOutObj::HEAD_BLOCK, id);
    } else goto ENDCHECK;
    startPos = fis.pos();
  } catch (JIOException* e) {
    delete e;
  }
ENDCHECK:
  close();
#endif
  broadcast(COUNT);
  broadcast(TOTAL);
  return (id != -1);
}

boolean JWaveFileObj::writeHeader(int _id) {
  id = -1;
  startPos = 0;
  count = 0;
  total = 0;
#if defined(WIN32)
  WAVEFORMATEX wfx;
  int fmtSize = sizeof(wfx)-2;
  wfx.wFormatTag = WAVE_FORMAT_PCM;
  wfx.nChannels = JWaveOutObj::channelValue[_id];
  wfx.nSamplesPerSec = JWaveOutObj::frequencyValue[_id];
  wfx.wBitsPerSample = JWaveOutObj::bitsValue[_id];
  nBlockAlign = wfx.nBlockAlign = wfx.nChannels*wfx.wBitsPerSample/8;
  wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
  wfx.cbSize = 0;
  blockSize = (wfx.nAvgBytesPerSec*
    JWaveOutObj::msPerBlock/1000)/
    wfx.nBlockAlign*wfx.nBlockAlign;
  try {
    int riffSize = 20+fmtSize;
    startPos = riffSize+8;
    fos << JBlock(4, "RIFF");
    fos << JBlock(riffSize);
    fos << JBlock(4, "WAVE");
    fos << JBlock(4, "fmt ");
    fos << JBlock(fmtSize);
    fos << JBlock(fmtSize, (char*)&wfx);
    fos << JBlock(4, "data");
    fos << JBlock(total);
  } catch (JIOException* e) {
    delete e;
    return false;
  }
#endif
  id = _id;
  repaint();
  broadcast(COUNT);
  broadcast(TOTAL);
  return true;
}

void JWaveFileObj::record() {
  cs.lock();
  if (recording) {
    cs.unlock();
    return;
  }
  close();
  id = -1;
  count = 0;
  try {
    fos.open(filename);
    bos.connect(fos);
    recording = true;
  } catch (JIOException* e) {
    delete e;
    close();
  }
  repaint();
  cs.unlock();
}

void JWaveFileObj::play() {
  cs.lock();
  if (playing) {
    cs.unlock();
    return;
  }
  close();
  try {
    if (check(true)) {
      pos = max(0, min(total, pos));
      pos = pos/nBlockAlign*nBlockAlign;
      fis.open(filename);
      fis.seek(startPos+pos);
      bis.connect(fis);
      playing = true;
      thread = JThread(this);
      thread.start();
      thread.setPriority(JThread::TNORM_PRIORITY+1);
    }
  } catch (JIOException* e) {
    delete e;
    close();
  }
  repaint();
  cs.unlock();
}

void JWaveFileObj::close() {
  cs.lock();
  if (recording) {
    recording = false;
    try {
      int riffSize = startPos+total-8;
      bos.flush();
      fos.seek(4);
      fos << JBlock(riffSize);
      fos.seek(startPos-4);
      fos << JBlock(total);
      bos.close();
    } catch (JIOException* e) {
      delete e;
    }
    repaint();
  }
  if (playing) {
    playing = false;
    closeHandle();
    repaint();
  }
  cs.unlock();
}

int JWaveFileObj::inputType(int n) 
{ return (n == IN_BLOCK) ? JWaveData::id : JRecorderObj::inputType(n);}
int JWaveFileObj::outputType(int n)
{ return (n == OUT_BLOCK) ? JWaveData::id : JRecorderObj::outputType(n);}
void JWaveFileObj::access(int n, JLinkObj& link, const JDataType& _data) 
{ _data.assign(data);}

JFRect JWaveFileObj::inputArea(int n) { 
  if (n < IN_LAST) return topArea(n, 0, IN_LAST);
  if (n >= IN_BLOCK) return leftArea(n, IN_BLOCK, N, 0, 1);
  return JFRect();
}

JFPoint JWaveFileObj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_LAST) return topPoint(n, link, 0, IN_LAST);
  if (n >= IN_BLOCK) return leftPoint(n, link, IN_BLOCK, N, 0, 1);
  return JFPoint();
}

void JWaveFileObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  if (id == -1) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  drawText(g, "Wave", rect1);
  drawText(g, "Format", rect2);
  drawText(g, filename, rect3);
}

void JWaveFileObj::engine(int n, JLinkObj& link) {
  if (n == IN_BLOCK) {
#if defined(WIN32)
    cs.lock();
    if (recording && !pause) {
      int nid;
      WAVEHDR *whdr;
      JBlock idata;
      link.access(JBlockData(idata));
      if (idata.size() < sizeof(WAVEHDR)) {
	cs.unlock();
	return;
      }
      idata.Dereference();
      whdr = (WAVEHDR*)(char*)idata;
      whdr->lpData = (LPSTR)(whdr+1);
      nid = max(0, HIWORD(whdr->dwUser));
      if (id == -1) writeHeader(nid);
      if (nid != id) {
	cs.unlock();
	close();
	return;
      }
      try {
        bos << JBlock(whdr->dwBytesRecorded, whdr->lpData);
	count = (total += whdr->dwBytesRecorded);
	broadcast(COUNT);
	broadcast(TOTAL);
        if (feedback) {
          link.access(JBlockData(data));
	  broadcast(OUT_BLOCK);
        }
	if (whdr->dwUser & JWaveOutObj::TAIL_BLOCK)
	  close();
      } catch (JIOException* e) {
        delete e;
	close();
      }
    }
    cs.unlock();
#endif
  } else JRecorderObj::engine(n, link);
}

DllImport void segmentDelay(int interval, int&base, int& counter, boolean& cond);

void JWaveFileObj::run() {
  int counter;
  int dataSize = total-pos;
  int base = JSystem::currentTimeMillis();
  count = pos;
  broadcast(COUNT);
  while (playing && (dataSize > 0)) {
    while (pause && playing)
      JThread::sleep(100);
#if defined(WIN32)
    WAVEHDR *whdr = (WAVEHDR*)(char*)data;
    whdr->dwBytesRecorded = min(blockSize, dataSize);
    whdr->dwBufferLength = whdr->dwBytesRecorded;
    if (dataSize <= blockSize) whdr->dwUser |= JWaveOutObj::TAIL_BLOCK;
    try {
      bis >> JBlock(whdr->dwBytesRecorded, whdr->lpData);
    } catch (JIOException *e) {
      delete e;
      break;
    }
    dataSize -= whdr->dwBytesRecorded;
    count += whdr->dwBytesRecorded;
    broadcast(OUT_BLOCK);
    broadcast(COUNT);
    whdr->dwUser = MAKELONG(JWaveOutObj::NORM_BLOCK, id);
    if (!dataSize) {
      if (repeat) {
        dataSize = total;
	fis.seek(startPos);
	bis.connect(fis);
        count = 0;
        broadcast(COUNT);
      } else break;
    }
#endif
    if (waveFeedback != JWaveOutObj::PAUSE) 
      segmentDelay(JWaveOutObj::msPerBlock, 
        base, counter, playing);
  }
  if (playing) {
    playing = false;
    closeHandle();
    repaint();
  }
}

