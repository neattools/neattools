#include "JStringProperty.h"
#include "JInteger.h"
#include "JInputBox.h"

char* theJStringProperty = JStringProperty().Register();
void JStringProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putString(os, "value", value);
}

void JStringProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = getString(dict, "value");
}

const char* JStringProperty::className() const { return "JStringProperty";}
JObject* JStringProperty::clone() const { return new JStringProperty(*this);}

int JStringProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = name.compareTo(((JStringProperty*)&s)->name);
  if (!result) 
    return value.compareTo(((JStringProperty*)&s)->value);
  return result;
}

JStringProperty::JStringProperty() {}
JStringProperty::JStringProperty(JString name, JString _value) 
  : JProperty(name) 
{ value = _value;}

JString JStringProperty::toJString() 
{ return name+"=\""+value+"\"";}

boolean JStringProperty::edit(int x, int y) {
  JString ov = value;
  if (JInputBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, 
    value, x, y) == JMessageBox::OK) {
    check();
  }
  return (value != ov);
}