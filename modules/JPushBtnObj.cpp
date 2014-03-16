#include "JPushBtnObj.h"
#include "JIntegerListProperty.h"

char* theJPushBtnObj = JPushBtnObj().Register();
void JPushBtnObj::writeContent(JOutputStream& os) {
  JBtnObj::writeContent(os);
  putInteger(os, "autoRepeat", autoRepeat);
}

void JPushBtnObj::readContent(JDictionary& dict) {
  JBtnObj::readContent(dict);
  autoRepeat = getInteger(dict, "autoRepeat", true);
}

const char* JPushBtnObj::className() const { return "JPushBtnObj";}
JObject* JPushBtnObj::clone() const { return new JPushBtnObj(*this);}
JPushBtnObj::JPushBtnObj() { 
  bkgnd = JColor::green.darker();
  autoRepeat = true;
}

boolean JPushBtnObj::mouseDown(JEvent& e, double x, double y) {
  if (e.modifiers & JEvent::LBUTTON) {
    if (inside(x, y)) {
      if (e.id == JEvent::MOUSE_DOWN) {
        mousePressed = true;
        setValue(mask);
      } else if (autoRepeat) {
        value = 0;
        broadcast(0);
        value = mask;
        broadcast(0);
      }
    }
  }
  return true;
}

JArray JPushBtnObj::getProperties() {
  JArray properties = JBtnObj::getProperties();
  properties.append(JIntegerListProperty("autoRepeat", autoRepeat, 
    JIntegerListProperty::booleanTag));
  return properties;
}

boolean JPushBtnObj::updateProperty(JProperty& prop) {
  if (JBtnObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("autoRepeat")) {
    autoRepeat = ((JIntegerListProperty*)&prop)->value;
    return true;
  }
  return false;
}

