#include "JAudioCodecObj.h"
#include "JLinkObj.h"
#include "JBlock.h"
#include "JWaveData.h"
#include "JCWaveData.h"
#include "JWaveOutObj.h"
#include "JInteger.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JComponent.h"
#include "JWindow.hpp"

char* theJAudioCodecObj = JAudioCodecObj().Register();

void JAudioCodecObj::writeContent(JOutputStream& os) {
  JModuleObj::writeContent(os);
  putInteger(os, "encodeType", encodeId);
  putInteger(os, "encodeType", encodeType);
  putInteger(os, "samplingFactor", samplingFactor);
}

void JAudioCodecObj::readContent(JDictionary& dict) {
  JModuleObj::readContent(dict);
  encodeType = getInteger(dict, "encodeId");
  encodeType = getInteger(dict, "encodeType");
  samplingFactor = getInteger(dict, "samplingFactor");
  encodeType = max(0, min(2, encodeType));
  samplingFactor = max(1, min(2, samplingFactor));
}

const char* JAudioCodecObj::className() const { return "JAudioCodecObj";}
JObject* JAudioCodecObj::clone() const { return new JAudioCodecObj(*this);}

enum { ENCODE_4BITS, ENCODE_3BITS, ENCODE_5BITS};
char* encodeIdTag[] = { "G723", /*"MPEG", */null};
char* encodeTypeTag[] = { "4bits", "3bits", "5bits", null};
int encodeTypeValue[] = { 4, 3, 5};

JAudioCodecObj::JAudioCodecObj() {
  igm = 2;
  ogm = 2;
  encodeId = 0;
  encodeType = 0;
  samplingFactor = 1;
  bitRate = 0;
}

void JAudioCodecObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, "ACodec", rect1);
  drawText(g, JInteger::toJString(bitRate)+"kbs", rect2);
}

void JAudioCodecObj::access(int n, JLinkObj& link, const JDataType& _data)
{ _data.assign((!n) ? encode : decode);}
int JAudioCodecObj::inputType(int n) { return (!n) ? JWaveData::id : JCWaveData::id;}
int JAudioCodecObj::outputType(int n) { return (!n) ? JCWaveData::id : JWaveData::id;}
boolean JAudioCodecObj::inputAllowed(int n) { return (boolean)(!inputSet(n).last());}
boolean JAudioCodecObj::outputAllowed(int n) { return true;}
JString JAudioCodecObj::inputTag(int n) { return (!n) ? "wave-in" : "encode-in";}
JString JAudioCodecObj::outputTag(int n) { return (!n) ? "encode-out" : "wave-out";}
int JAudioCodecObj::inputFace(int n) { return (!n) ? LEFT: TOP;}
int JAudioCodecObj::outputFace(int n) { return (!n) ? RIGHT: BOTTOM;}
JFRect JAudioCodecObj::inputArea(int n) 
{ return (!n) ? leftArea(n, 0, 1) : topArea(n, 1, 1);}
JFRect JAudioCodecObj::outputArea(int n) 
{ return (!n) ? rightArea(n, 0, 1) : bottomArea(n, 1, 1);}
JFPoint JAudioCodecObj::inputPoint(int n, JLinkObj& link) 
{ return (!n) ? leftPoint(n, link, 0, 1) : topPoint(n, link, 1, 1);}
JFPoint JAudioCodecObj::outputPoint(int n, JLinkObj& link) 
{ return (!n) ? rightPoint(n, link, 0, 1) : bottomPoint(n, link, 1, 1);}

int packBits(uchar*& buf, unsigned code, int bits,
  unsigned &out_buf, int &out_bits) {
  out_buf |= (code << out_bits);
  out_bits += bits;
  if (out_bits >= 8) {
    *buf++ = out_buf & 0xff;
    out_bits -= 8;
    out_buf >>= 8;
  }
  return (out_bits > 0);
}

int unpackBits(uchar*& buf, unsigned char &code, int bits,
  unsigned &in_buf, int &in_bits) {
  if (in_bits < bits) {
    in_buf |= (((unsigned)*buf++) << in_bits);
    in_bits += 8;
  }
  code = in_buf & ((1 << bits) - 1);
  in_buf >>= bits;
  in_bits -= bits;
  return (in_bits > 0);
}

void JAudioCodecObj::engine(int n, JLinkObj& link) {
#if defined(WIN32)
  JBlock data;
  link.access(JBlockData(data));
  if (data.size() < sizeof(WAVEHDR)) return;
  data.Dereference();
  WAVEHDR *whdr = (WAVEHDR*)(char*)data;
  ushort nid = HIWORD(whdr->dwUser);
  ushort compressId = nid >> 4;
  nid = nid & 0xF;
  int i, j;
  int frequency = JWaveOutObj::frequencyValue[nid];
  int channel = JWaveOutObj::channelValue[nid];
  int bits = JWaveOutObj::bitsValue[nid];
  int length = whdr->dwBufferLength;
  whdr->lpData = (LPSTR)(whdr+1);
  if (!n) {
    if (compressId || (nid >= JWaveOutObj::_LAST)) return;
    int factor = samplingFactor*channel*bits/8;
    int type = encodeTypeValue[encodeType];
    int blockSize = (length*type+bits-1)/bits;
    int size = sizeof(WAVEHDR)+blockSize;
    if (whdr->dwUser & JWaveOutObj::HEAD_BLOCK)
      enc_state2 = enc_state = JG723State();
    encode = JBlock(size, 0);
    WAVEHDR *whdr2 = (WAVEHDR*)(char*)encode;
    *whdr2 = *whdr;
    whdr2->lpData = (LPSTR)(whdr2+1);
    whdr2->dwUser = MAKELONG(LOWORD(whdr->dwUser), 
      (((((encodeId<<4)+encodeType)<<4)+samplingFactor)<<4)+nid);
    char* buf = (char*)whdr->lpData;
    uchar* buf2 = (uchar*)whdr2->lpData;
    short (*encoder)(int, int, JG723State&);
    int out_bits = 0, resid = 0;
    unsigned out_buf = 0;
    int code, code2;
    switch (encodeType) {
      case ENCODE_3BITS: encoder = JG723::encode3; break;
      case ENCODE_5BITS: encoder = JG723::encode5; break;
      default: encoder = JG723::encode4;
    }
    int newBitRate = frequency*channel*type/(samplingFactor*1000);
    if (newBitRate != bitRate) {
      bitRate = newBitRate;
      repaint();
    }
    if (bits == 8) {
      for (i=0; i<length; i+=factor) {
        code = (*encoder)(((short)buf[i])<<8, JG723::LINEAR, enc_state);
        resid = packBits(buf2, code, type, out_buf, out_bits);
        if (channel == 2) {
          code2 = (*encoder)(((short)buf[i+1])<<8, JG723::LINEAR, enc_state2);
   	  resid = packBits(buf2, code2, type, out_buf, out_bits);
        }
      }
    } else {
      for (i=0; i<length; i+=factor) {
        code = (*encoder)(*(short*)(buf+i), JG723::LINEAR, enc_state);
        resid = packBits(buf2, code, type, out_buf, out_bits);
        if (channel == 2) {
          code2 = (*encoder)(*(short*)(buf+i+2), JG723::LINEAR, enc_state2);
   	  resid = packBits(buf2, code2, type, out_buf, out_bits);
        }
      }
    }
    while (resid) resid = packBits(buf2, 0, type, out_buf, out_bits);
  } else {
    if (!compressId) return;
    int decodeId = (compressId>>8) & 0xF;
    int decodeType = (compressId>>4) & 0xF;
    int decodeFactor = compressId & 0xF;
    int cell = channel*bits/8;
    int factor = decodeFactor*cell;
    int type = encodeTypeValue[decodeType];
    int size = sizeof(WAVEHDR)+length;
    if (whdr->dwUser & JWaveOutObj::HEAD_BLOCK)
      dec_state2 = dec_state = JG723State();
    decode = JBlock(size, 0);
    WAVEHDR *whdr2 = (WAVEHDR*)(char*)decode;
    *whdr2 = *whdr;
    whdr2->lpData = (LPSTR)(whdr2+1);
    whdr2->dwUser = MAKELONG(LOWORD(whdr->dwUser), nid);
    uchar* buf = (uchar*)whdr->lpData;
    char* buf2 = (char*)whdr2->lpData;
    short (*decoder)(int, int, JG723State&);
    int in_bits = 0;
    unsigned in_buf = 0;
    unsigned char code, code2;
    switch (decodeType) {
      case ENCODE_3BITS: decoder = JG723::decode3; break;
      case ENCODE_5BITS: decoder = JG723::decode5; break;
      default: decoder = JG723::decode4;
    }
    int newBitRate = frequency*channel*type/(decodeFactor*1000);
    if (newBitRate != bitRate) {
      bitRate = newBitRate;
      repaint();
    }
    if (bits == 8) {
      for (i=0; i<length; i+=factor) {
 	unpackBits(buf, code, type, in_buf, in_bits);
        buf2[i] = (*decoder)(code, JG723::LINEAR, dec_state) >> 8;
        for (j=cell; j<factor; j+=cell)
          buf2[i+j] = (dec_state.prev*j+buf2[i]*(factor-j))/factor;
        dec_state.prev = buf2[i];
        if (channel == 2) {
   	  unpackBits(buf, code2, type, in_buf, in_bits);
          buf2[i+1] = (*decoder)(code2, JG723::LINEAR, dec_state2) >> 8;
          for (j=cell; j<factor; j+=cell)
            buf2[i+j+1] = (dec_state2.prev*j+buf2[i+1]*(factor-j))/factor;
          dec_state2.prev = buf2[i+1];
        }
      }
    } else {
      for (i=0; i<length; i+=factor) {
 	unpackBits(buf, code, type, in_buf, in_bits);
        *(ushort*)(buf2+i) = (*decoder)(code, JG723::LINEAR, dec_state);
        for (j=cell; j<factor; j+=cell)
          *(short*)(buf2+i+j) = (dec_state.prev*j+*(short*)(buf2+i)*(factor-j))/factor;
        dec_state.prev = *(short*)(buf2+i);
        if (channel == 2) {
   	  unpackBits(buf, code2, type, in_buf, in_bits);
          *(ushort*)(buf2+i+2) = (*decoder)(code2, JG723::LINEAR, dec_state2);
          for (j=cell; j<factor; j+=cell)
            *(short*)(buf2+i+j+2) = (dec_state2.prev*j+*(short*)(buf2+i+2)*(factor-j))/factor;
          dec_state2.prev = *(short*)(buf2+i+2);
        }
      }
    }
  }
  broadcast(n);
#endif
}

JArray JAudioCodecObj::getProperties() {
  JArray properties = JModuleObj::getProperties();
  properties.append(JIntegerListProperty("encodeId", encodeId, encodeIdTag));
  properties.append(JIntegerListProperty("encodeType", encodeType, encodeTypeTag));
  properties.append(JIntegerProperty("samplingFactor", samplingFactor, 1, 2));
  return properties;
}

boolean JAudioCodecObj::updateProperty(JProperty& prop) {
  if (JModuleObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("encodeId")) {
    encodeId = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("encodeType")) {
    encodeType = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("samplingFactor")) {
    samplingFactor = ((JIntegerProperty*)&prop)->value;
    return true;
  }
  return false;
}

