#include "JRealProperty.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JInputBox.h"
#include "JMath.h"

char* theJRealProperty = JRealProperty().Register();
void JRealProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putDouble(os, "value", value);
  putInteger(os, "w", w);
  putInteger(os, "f", f);
}

void JRealProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = getDouble(dict, "value");
  w = getInteger(dict, "w");
  f = getInteger(dict, "f");
}

const char* JRealProperty::className() const { return "JRealProperty";}
JObject* JRealProperty::clone() const { return new JRealProperty(*this);}

int JRealProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = name.compareTo(((JRealProperty*)&s)->name);
  if (!result) 
    return cmp(value, ((JRealProperty*)&s)->value);
  return result;
}

JRealProperty::JRealProperty() {}
JRealProperty::JRealProperty(JString name, double _value) 
  : JProperty(name) { value = _value; w = f = 0;}
JRealProperty::JRealProperty(JString name, double _value, int _w, int _f) 
  : JProperty(name) { value = _value; w = _w; f = _f;}

JString JRealProperty::toJString() 
{ return name+"="+JDouble::toJStringF(value, w, f);}

boolean JRealProperty::edit(int x, int y) {
  double ov = value;
  JString data = JDouble::toJStringF(value, w, f);
  if (JInputBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, 
    data, x, y) == JMessageBox::OK) {
    check();
    value = (double)JDouble(data);
  }
  return (value != ov);
}