#include "JItoWObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBlock.h"
#include "JWaveData.h"
#include "JWaveOutObj.h"
#include "JWindow.hpp"

char* theJItoWObj = JItoWObj().Register();
const char* JItoWObj::className() const { return "JItoWObj";}
JObject* JItoWObj::clone() const { return new JItoWObj(*this);}

JItoWObj::JItoWObj() { 
  igm = 2;
  fid = JWaveOutObj::_1M08;
  moduleColor = JWaveData::color;
#if defined(WIN32)
#endif
}

int JItoWObj::outputType(int n) { return JWaveData::id;}

JString JItoWObj::inputTag(int n) { 
  char* tag[] = {"inputL/Mono(16bits)", "inputR(16bits)"};
  return tag[n];
}

JFRect JItoWObj::inputArea(int n) 
{ return leftArea(n, 0, igm);}
JFPoint JItoWObj::inputPoint(int n, JLinkObj& link)
{ return leftPoint(n, link, 0, igm);}

void JItoWObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("ItoW"), rect);
}

void JItoWObj::access(int n, JLinkObj& link, const JDataType& data) 
{ data.assign(wave);}

void JItoWObj::engine(int n, JLinkObj& link) {
  int iv;
  link.access(JIntegerData(iv));
/*
  (short)iv;
  broadcast(0);
*/
}
