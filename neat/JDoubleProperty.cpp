#include "JDoubleProperty.h"
#include "JDouble.h"
#include "JInputBox.h"
#include "JMath.h"

char* theJDoubleProperty = JDoubleProperty().Register();
void JDoubleProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putDouble(os, "value", value);
  putDouble(os, "minimum", minimum);
  putDouble(os, "maximum", maximum);
}

void JDoubleProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = getDouble(dict, "value");
  minimum = getDouble(dict, "minimum");
  maximum = getDouble(dict, "maximum");
}

const char* JDoubleProperty::className() const { return "JDoubleProperty";}
JObject* JDoubleProperty::clone() const { return new JDoubleProperty(*this);}

int JDoubleProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = name.compareTo(((JDoubleProperty*)&s)->name);
  if (!result) result = cmp(value, ((JDoubleProperty*)&s)->value);
  return result;
}

JDoubleProperty::JDoubleProperty() {}
JDoubleProperty::JDoubleProperty(JString name, 
  double v, double _minimum, double _maximum) : JProperty(name) {
  value = v;
  minimum = _minimum;
  maximum = _maximum;
}

JString JDoubleProperty::toJString() { 
  return name+"["+JDouble::toJString(minimum)+
    "-"+JDouble::toJString(maximum)+
    "]="+JDouble::toJString(value);
}

boolean JDoubleProperty::check() { 
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

boolean JDoubleProperty::edit(int x, int y) {
  double ov = value;
  JString data = JDouble::toJString(value);
  if (JInputBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, 
    data, x, y) == JMessageBox::OK) {
    value = (double)JDouble(data);
    check();
  }
  return (value != ov);
}