#include "JIntegerObj.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JColorData.h"
#include "JStringData.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJIntegerObj = JIntegerObj().Register();

void JIntegerObj::writeContent(JOutputStream& os) {
  JLabelObj::writeContent(os);
  putInteger(os, "convertBase", convertBase);
}

void JIntegerObj::readContent(JDictionary& dict) {
  JLabelObj::readContent(dict);
  convertBase = getInteger(dict, "convertBase", 10);
  convertBase = max(2, min(36, convertBase));
  label = JInteger::toJString(value, convertBase);
}

const char* JIntegerObj::className() const { return "JIntegerObj";}
JObject* JIntegerObj::clone() const { return new JIntegerObj(*this);}

JIntegerObj::JIntegerObj() {
  color = JColor::cyan;
  bkgnd = JColor::black;
  igm = IN_LAST;
  ogm = OUT_LAST;
  convertBase = 10;
  label = JInteger::toJString(value, convertBase);
}

int JIntegerObj::inputType(int n) { 
  switch (n) {
    case IN_COLOR:
    case IN_BKGND: return JColorData::id;
    case IN_STRING: return JStringData::id;
  }
  return JIntegerData::id;
}

int JIntegerObj::outputType(int n) { 
  if (n == OUT_STRING) return JStringData::id;
  return JIntegerData::id;
}

JString JIntegerObj::inputTag(int n) {
  if (n == IN_STRING) return "string-in";
  return JLabelObj::inputTag(n);
}

JString JIntegerObj::outputTag(int n) {
  if (n == OUT_STRING) return "string-out";
  return JLabelObj::outputTag(n);
}

void JIntegerObj::access(int n, JLinkObj& link, const JDataType& data) { 
  switch (n) {
    case OUT_DATA :
      INT(data) = value;
      break;
    case OUT_STRING :
      JSTRING(data) = label;
      break;
    default:
      JLabelObj::access(n, link, data);
  }
}

void JIntegerObj::engine(int n, JLinkObj& link) {
  switch (n) {
    case IN_DATA: {
      int iv = value;
      link.access(JIntegerData(iv));
      setValue(iv);
      break;
    }
    case IN_STRING: {
	  JString iv = JInteger::toJString(value);
      link.access(JStringData(iv));
      setValue((int)JInteger(iv, convertBase));
      break;
    }
    default:
      JLabelObj::engine(n, link);
  }
}

JArray JIntegerObj::getProperties() {
  JArray properties = JLabelObj::getProperties();
  properties.append(JIntegerProperty("value", value, 
    JInteger::MIN_VALUE, JInteger::MAX_VALUE));
  properties.append(JIntegerProperty("convertBase", convertBase, 
    2, 36));
  return properties;
}

boolean JIntegerObj::updateProperty(JProperty& prop) {
  if (JLabelObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("value")) {
    setValue(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("convertBase")) {
    convertBase = ((JIntegerProperty*)&prop)->value;
    convertBase = max(2, min(36, convertBase));
    label = JInteger::toJString(value, convertBase);
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JIntegerObj::setValue(int _value) {
  if (value != _value) {
    value = _value;
    label = JInteger::toJString(value, convertBase);
    broadcast(OUT_DATA);
    broadcast(OUT_STRING);
    repaint();
    return true;
  }
  return false;
}

boolean JIntegerObj::setLabel(JString _label) { 
  if (setValue((int)JInteger(_label, convertBase))) return true;
  _label = JInteger::toJString(value, convertBase);
  if (_label != label) {
    label = _label;
    broadcast(OUT_STRING);
    repaintView(*this);
    return true;
  }
  return false;
}

JString JIntegerObj::getEditSet() { return "-0123456789";}
