#include "JSwitchObj.h"
#include "JLinkObj.h"
#include "JIntegerListProperty.h"

char* theJSwitchObj = JSwitchObj().Register();
void JSwitchObj::writeContent(JOutputStream& os) {
  JBtnObj::writeContent(os);
  putInteger(os, "depressOnly", depressOnly);
}

void JSwitchObj::readContent(JDictionary& dict) {
  JBtnObj::readContent(dict);
  depressOnly = getInteger(dict, "depressOnly");
}

const char* JSwitchObj::className() const { return "JSwitchObj";}
JObject* JSwitchObj::clone() const { return new JSwitchObj(*this);}

JSwitchObj::JSwitchObj() { 
  bkgnd = JColor::red.darker();
  depressOnly = false;
}

boolean JSwitchObj::mouseDown(JEvent& e, double x, double y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    if (inside(x, y)) {
      mousePressed = true;
      if (depressOnly) {
        if (value == 0) setValue(mask);
      } else setValue((value == 0) ? mask : 0);
    }
  }
  return true;
}

boolean JSwitchObj::mouseUp(JEvent& e, double x, double y) {
  if (mousePressed) {
    mousePressed = false;
  }
  return true;
}

JArray JSwitchObj::getProperties() {
  JArray properties = JBtnObj::getProperties();
  properties.append(JIntegerListProperty("depressOnly", depressOnly, 
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JSwitchObj::updateProperty(JProperty& prop) {
  if (JBtnObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("depressOnly")) {
    depressOnly = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

