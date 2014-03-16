#include "JFileProperty.h"
#include "JInteger.h"
#include "JFileBox.h"

char* theJFileProperty = JFileProperty().Register();
const char* JFileProperty::className() const { return "JFileProperty";}
JObject* JFileProperty::clone() const { return new JFileProperty(*this);}

JFileProperty::JFileProperty() {}
JFileProperty::JFileProperty(JString name, 
  JString _value, JString _type) 
  : JStringProperty(name, _value) { type = _type;}

boolean JFileProperty::edit(int x, int y) {
  JString ov = value;
  if (JFileBox::create(JString("Property Edit for ")+
    toJString(), value, type, x, y) == JMessageBox::OK) {
    check();
  }
  return (value != ov);
}