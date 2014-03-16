#include "JRealObj.h"
#include "JDouble.h"
#include "JLinkObj.h"
#include "JRealData.h"
#include "JColorData.h"
#include "JIntegerData.h"
#include "JStringData.h"
#include "JRealProperty.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"

char* theJRealObj = JRealObj().Register();
void JRealObj::writeContent(JOutputStream& os) {
  JLabelObj::writeContent(os);
  putDouble(os, "rval", rval);
  putInteger(os, "w", w);
  putInteger(os, "f", f);
}

void JRealObj::readContent(JDictionary& dict) {
  JLabelObj::readContent(dict);
  rval = getDouble(dict, "rval");
  w = getInteger(dict, "w");
  f = getInteger(dict, "f");
  label = JDouble::toJStringF(rval, w, f);
}

const char* JRealObj::className() const { return "JRealObj";}
JObject* JRealObj::clone() const { return new JRealObj(*this);}

JRealObj::JRealObj() {
  color = JColor::cyan;
  bkgnd = JColor::black;
  igm = IN_LAST;
  ogm = OUT_LAST;
  rval = 0.0; w=3; f=1;
  label = JDouble::toJStringF(rval, w, f);
}

int JRealObj::inputType(int n) { 
  switch (n) {
    case IN_DATA: return JRealData::id;
    case IN_COLOR:
    case IN_BKGND: return JColorData::id;
    case IN_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

int JRealObj::outputType(int n) { 
  switch (n) {
    case OUT_DATA: return JRealData::id;
    case OUT_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

JString JRealObj::inputTag(int n) {
  if (n == IN_STRING) return "string-in";
  return JLabelObj::inputTag(n);
}

JString JRealObj::outputTag(int n) {
  if (n == OUT_STRING) return "string-out";
  return JLabelObj::outputTag(n);
}

void JRealObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case OUT_DATA :
      DOUBLE(data) = rval;
      break;
    case OUT_STRING :
      JSTRING(data) = label;
      break;
    default:
      JLabelObj::access(n, link, data);
  }
}

void JRealObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      double iv = rval;
      link.access(JRealData(iv));
      setRValue(iv);
      break;
    }
    case IN_STRING: {
	  JString iv = JDouble::toJString(rval);
      link.access(JStringData(iv));
      setRValue((double)JDouble(iv));
      break;
    }
    default:
      JLabelObj::engine(n, link);
  }
}

JArray JRealObj::getProperties() {
  JArray properties = JLabelObj::getProperties();
  properties.append(JRealProperty("rval", rval, w, f));
  properties.append(JIntegerProperty("width", w, 3, 20));
  properties.append(JIntegerProperty("float", f, 1, w-2));
  return properties;
}

boolean JRealObj::updateProperty(JProperty& prop) {
  if (JLabelObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("rval")) {
    setRValue(((JRealProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("width")) {
    w = ((JIntegerProperty*)&prop)->value;
    setLabel(label);
    return true;
  } else if (prop.getName() == JString("float")) {
    f = ((JIntegerProperty*)&prop)->value;
    setLabel(label);
    return true;
  }
  return false;
}

boolean JRealObj::setRValue(double _rval) {
  if (_rval != rval) {
    rval = _rval;
    label = JDouble::toJStringF(rval, w, f);
    broadcast(OUT_DATA);
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JRealObj::setLabel(JString _label) { 
  if (setRValue((double)JDouble(_label))) return true;
  _label = JDouble::toJStringF(rval, w, f);
  if (_label != label) {
    label = _label;
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

JString JRealObj::getEditSet() { return "-0123456789.";}
