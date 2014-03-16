#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JBlockData.h"
#include "JStringData.h"
#include "JRealData.h"
#include "JDateData.h"
#include "JComplexData.h"
#include "JInteger.h"
#include "JBlock.h"
#include "JString.h"
#include "JDouble.h"
#include "JColor.h"
#include "JDate.h"
#include "JComplex.h"

const char* JDataType::className() const { return "JDataType";}
const char* JDataType::sid() const { return "";}

enum { BLOCK, INTEGER, REAL, STRING, COLOR, MIDI, WAVE,
  VIDEO, BYTES, DATETIME, CWAVE, CVIDEO, COMPLEX, MATRIX};
char* JDataType::tag[] = {
  "block", "integer", "real",
  "string", "color", "midi", 
  "wave", "video", "bytes", 
  "date", "cWave", "cVideo", 
  "complex", "matrix", null
};

JString JDataType::str = "KIRSCMWVBDwvcm";
JString JDataType::bstr = "KWVBwvm";
int JDataType::last = str.length();
int JDataType::convertBase = 128;
const JColor JDataType::color = JColor::cyan.darker();
const int JDataType::id = -1;

JArray JDataType::getDataArray() {
  JArray data;
  data.append(JBlock());
  data.append(JInteger());
  data.append(JDouble());
  data.append(JString());
  data.append(JInteger());
  data.append(JInteger());
  data.append(JBlock());
  data.append(JBlock());
  data.append(JBlock());
  data.append(JDate());
  data.append(JBlock());
  data.append(JBlock());
  data.append(JComplex());
  data.append(JBlock());
  return data;
}

JObject* JDataType::create(int id, JLinkObj& link) {
  JObject *obj = null;
  switch (str[id]) {
    case 'I':
    case 'M':
    case 'C':
      obj = new JInteger;
      link.access(JIntegerData((int)*(JInteger*)obj));
      break;
    case 'c':
      obj = new JComplex;
      link.access(JComplexData(*(JComplex*)obj));
      break;
    case 'D':
      obj = new JDate;
      link.access(JDateData(*(JDate*)obj));
      break;
    case 'R':
      obj = new JDouble;
      link.access(JRealData((double)*(JDouble*)obj));
      break;
    case 'S':
      obj = new JString;
      link.access(JStringData(*(JString*)obj));
      break;
    default: {
      obj = new JBlock;
      link.access(JBlockData(*(JBlock*)obj));
      break;
    }
  }
  return obj;
}

JObject* JDataType::create(int id, const JBlock& item) {
  JObject *obj = null;
  switch (str[id]) {
    case 'I':
    case 'M':
    case 'C':
      obj = new JInteger(JString(item), convertBase);
      break;
    case 'c':
      obj = new JComplex(JString(item));
      break;
    case 'D':
      obj = new JDate(JString(item));
      break;
    case 'R':
      obj = new JDouble(JString(item));
      break;
    case 'S':
      obj = new JString(item);
      break;
    default: {
      obj = new JBlock(item);
      break;
    }
  }
  return obj;
}

JObject* JDataType::createTag(int &id, const JBlock& item) {
  if (item.size()) {
    id = str.indexOf(item[0]);
    if (id > -1) {
      if (bstr.indexOf(item[0]) > -1) {
        JString tag(item);
        return create(id, JBlock(
          (int)JInteger(tag(1), convertBase), 
          ((char*)item)+(tag.length()+1)));
      }
      return create(id, JBlock(item.size()-1, 
        ((char*)item)+1));
    }
  } else id = -1;
  return null;
}

JBlock JDataType::toBlock(int id, const JObject& obj) {
  JBlock block;
  switch (str[id]) {
    case 'I':
    case 'M':
    case 'C':
      block = JBlock(JInteger::toJString(
        (int)*(JInteger*)&obj, convertBase),
        JBlock::needCopy);
      break;
    case 'c':
      block = JBlock(((JComplex*)&obj)->toJString(),
        JBlock::needCopy);
      break;
    case 'D':
      block = JBlock(((JDate*)&obj)->toJString(),
        JBlock::needCopy);
      break;
    case 'R':
      block = JBlock(JDouble::toJString(
        (double)*(JDouble*)&obj),
        JBlock::needCopy);
      break;
    case 'S':
      block = JBlock(*(JString*)&obj, JBlock::needCopy);
      break;
    default: {
      block = *(JBlock*)&obj;
      break;
    }
  }
  return block;
}

JBlock JDataType::toTagBlock(int id, const JObject& obj) { 
  if (bstr.indexOf(str[id]) > -1) {
    JBlock block = *(JBlock*)&obj;
    JString prefix = JInteger::toJString(
      block.size(), convertBase);
    return JBlock(str[id])+JBlock(prefix)+block;
  }
  return JBlock(str[id])+toBlock(id, obj);
}
