#include "JIntegerProperty.h"
#include "JInteger.h"
#include "JIntegerBox.h"

char* theJIntegerProperty = JIntegerProperty().Register();
void JIntegerProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putInteger(os, "value", value);
  putInteger(os, "minimum", minimum);
  putInteger(os, "maximum", maximum);
}

void JIntegerProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = getInteger(dict, "value");
  minimum = getInteger(dict, "minimum");
  maximum = getInteger(dict, "maximum");
}

const char* JIntegerProperty::className() const { return "JIntegerProperty";}
JObject* JIntegerProperty::clone() const { return new JIntegerProperty(*this);}

int JIntegerProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = name.compareTo(((JIntegerProperty*)&s)->name);
  if (!result) result = value-((JIntegerProperty*)&s)->value;
  return result;
}

JIntegerProperty::JIntegerProperty() {}
JIntegerProperty::JIntegerProperty(JString name, 
  int v, int min, int max) : JProperty(name) {
  value = v;
  minimum = min;
  maximum = max;
}

JString JIntegerProperty::toJString() { 
  return name+"["+JInteger::toJString(minimum)+
    "-"+JInteger::toJString(maximum)+
    "]="+JInteger::toJString(value);
}

boolean JIntegerProperty::check() { 
  if (value > maximum) {
    value = maximum;
    return true;
  }
  if (value < minimum) {
    value = minimum;
    return true;
  }
  return false;
}

boolean JIntegerProperty::edit(int x, int y) {
  int ov = value;
  if (JIntegerBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, 
    value, minimum, maximum, x, y) == JMessageBox::OK) {
    check();
  }
  return (value != ov);
}