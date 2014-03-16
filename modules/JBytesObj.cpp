#include "JBytesObj.h"
#include "JIntegerData.h"
#include "JBytesData.h"
#include "JColorData.h"
#include "JStringData.h"
#include "JStringProperty.h"
#include "JLinkObj.h"

char* theJBytesObj = JBytesObj().Register();

void JBytesObj::writeContent(JOutputStream& os) {
  JLabelObj::writeContent(os);
  putString(os, "data", JBlock::toJString(data));
}

void JBytesObj::readContent(JDictionary& dict) {
  JLabelObj::readContent(dict);
  label = getString(dict, "data");
  data = JBlock::parse(label);
}

const char* JBytesObj::className() const { return "JBytesObj";}
JObject* JBytesObj::clone() const { return new JBytesObj(*this);}

JBytesObj::JBytesObj() {
  color = JBytesData::color;
  bkgnd = JColor::black;
  igm = IN_LAST;
  ogm = OUT_LAST;
  label = JBlock::toJString(data);
}

int JBytesObj::inputType(int n) { 
  switch (n) {
    case IN_COLOR:
    case IN_BKGND: return JColorData::id;
    case IN_STRING: return JStringData::id;
	case IN_DATA: return JBytesData::id;
  }
  return JIntegerData::id;
}

int JBytesObj::outputType(int n) { 
  if (n == OUT_STRING) return JStringData::id;
  else if (n == OUT_DATA) return JBytesData::id;
  return JIntegerData::id;
}

JString JBytesObj::inputTag(int n) {
  if (n == IN_STRING) return "string-in";
  return JLabelObj::inputTag(n);
}

JString JBytesObj::outputTag(int n) {
  if (n == OUT_STRING) return "string-out";
  return JLabelObj::outputTag(n);
}

void JBytesObj::access(int n, JLinkObj& link, const JDataType& v) { 
  switch (n) {
    case OUT_DATA :
      JBLOCK(v) = data;
      break;
    case OUT_STRING :
      JSTRING(v) = label;
      break;
    default:
      JLabelObj::access(n, link, v);
  }
}

void JBytesObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
	  JBlock iv;
      link.access(JBytesData(iv));
      setValue(iv);
      break;
    }
    case IN_STRING: {
	  JString iv;
      link.access(JStringData(iv));
      setLabel(iv);
      break;
    }
    default:
      JLabelObj::engine(n, link);
  }
}

boolean JBytesObj::setValue(JBlock _data) {
  if (data != _data) {
    data = _data;
    label = JBlock::toJString(data);
    broadcast(OUT_DATA);
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JBytesObj::setLabel(JString _label) {
  if (setValue(JBlock::parse(_label))) return true;
  _label = JBlock::toJString(data);
  if (_label != label) {
    label = _label;
    broadcast(OUT_STRING);
    repaintView(*this);
    return true;
  }
  return false;
}

JString JBytesObj::getEditSet() { return "0123456789ABCDEF";}
