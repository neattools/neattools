#include "JRealComplexObj.h"
#include "JDouble.h"
#include "JComplex.h"
#include "JLinkObj.h"
#include "JRealData.h"
#include "JComplexData.h"
#include "JColorData.h"
#include "JIntegerData.h"
#include "JStringData.h"
#include "JRealProperty.h"
#include "JIntegerProperty.h"
#include "JColorProperty.h"

char* theJRealComplexObj = JRealComplexObj().Register();
void JRealComplexObj::writeContent(JOutputStream& os) {
  JLabelObj::writeContent(os);
  putDouble(os, "real", cval.r);
  putDouble(os, "imag", cval.i);
  putInteger(os, "w", w);
  putInteger(os, "f", f);
}

void JRealComplexObj::readContent(JDictionary& dict) {
  JLabelObj::readContent(dict);
  cval.r = getDouble(dict, "real");
  cval.i = getDouble(dict, "imag");
  w = getInteger(dict, "w");
  f = getInteger(dict, "f");
  label = JComplex::toJStringF(cval, w, f);
}

const char* JRealComplexObj::className() const { return "JRealComplexObj";}
JObject* JRealComplexObj::clone() const { return new JRealComplexObj(*this);}

JRealComplexObj::JRealComplexObj() {
  color = JColor::cyan;
  bkgnd = JColor::black;
  igm = IN_LAST;
  ogm = OUT_LAST;
  w=3; f=1;
  label = JComplex::toJStringF(cval, w, f);
}

int JRealComplexObj::inputType(int n) { 
  switch (n) {
    case IN_DATA: return JComplexData::id;
    case IN_COLOR:
    case IN_BKGND: return JColorData::id;
    case IN_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

int JRealComplexObj::outputType(int n) { 
  switch (n) {
    case OUT_DATA: return JComplexData::id;
    case OUT_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

JString JRealComplexObj::inputTag(int n) {
  if (n == IN_STRING) return "string-in";
  return JLabelObj::inputTag(n);
}

JString JRealComplexObj::outputTag(int n) {
  if (n == OUT_STRING) return "string-out";
  return JLabelObj::outputTag(n);
}

void JRealComplexObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case OUT_DATA :
      JCOMPLEX(data) = cval;
      break;
    case OUT_STRING :
      JSTRING(data) = label;
      break;
    default:
      JLabelObj::access(n, link, data);
  }
}

void JRealComplexObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      jcomplex iv = cval;
      link.access(JComplexData(iv));
      setCValue(iv);
      break;
    }
    case IN_STRING: {
	  JString iv = JComplex::toJString(cval);
      link.access(JStringData(iv));
      setCValue((jcomplex)JComplex(iv));
      break;
    }
    default:
      JLabelObj::engine(n, link);
  }
}

JArray JRealComplexObj::getProperties() {
  JArray properties = JLabelObj::getProperties();
  properties.append(JRealProperty("real", cval.r, w, f));
  properties.append(JRealProperty("imag", cval.i, w, f));
  properties.append(JIntegerProperty("width", w, 3, 20));
  properties.append(JIntegerProperty("float", f, 1, w-2));
  return properties;
}

boolean JRealComplexObj::updateProperty(JProperty& prop) {
  if (JLabelObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("real")) {
    setCValue(jcomplex(((JRealProperty*)&prop)->value, cval.i));
    return true;
  } else if (prop.getName() == JString("imag")) {
    setCValue(jcomplex(cval.r, ((JRealProperty*)&prop)->value));
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

boolean JRealComplexObj::setCValue(jcomplex _cval) {
  if (_cval != cval) {
    cval = _cval;
    label = JComplex::toJStringF(cval, w, f);
    broadcast(OUT_DATA);
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JRealComplexObj::setLabel(JString _label) { 
  if (setCValue((jcomplex)JComplex(_label))) return true;
  _label = JComplex::toJStringF(cval, w, f);
  if (_label != label) {
    label = _label;
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

JString JRealComplexObj::getEditSet() { return "-0123456789.,i";}
