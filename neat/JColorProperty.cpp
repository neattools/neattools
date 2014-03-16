#include "JColorProperty.h"
#include "JInteger.h"
#include "JColorBox.h"

char* theJColorProperty = JColorProperty().Register();
void JColorProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putObject(os, "color", color);
}

void JColorProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  color = *(JColor*)getObject(dict, "color");
}

const char* JColorProperty::className() const { return "JColorProperty";}
JObject* JColorProperty::clone() const { return new JColorProperty(*this);}

int JColorProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  return color.compareTo(((JColorProperty*)&s)->color);
}

JColorProperty::JColorProperty() {}
JColorProperty::JColorProperty(JString name, 
  JColor c) : JProperty(name) {
  color = c;
}

JString JColorProperty::toJString() { 
  return name+"=("+
    JInteger::toJString(color.getRed())+","+
    JInteger::toJString(color.getGreen())+","+
    JInteger::toJString(color.getBlue())+")";
}

boolean JColorProperty::edit(int x, int y) {
  JColor oc = color;
  if (JColorBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, color, x, y) ==
    JMessageBox::OK) {
    check();
  }
  return (color != oc);
}