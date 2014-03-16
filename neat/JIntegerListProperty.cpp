#include "JIntegerListProperty.h"
#include "JInteger.h"
#include "JIntegerListBox.h"

char* theJIntegerListProperty = JIntegerListProperty().Register();
char* JIntegerListProperty::booleanTag[] = { "false", "true", null};

void JIntegerListProperty::writeContent(JOutputStream& os) {
  JProperty::writeContent(os);
  putInteger(os, "value", value);
  putObject(os, "tag", tag);
}

void JIntegerListProperty::readContent(JDictionary& dict) {
  JProperty::readContent(dict);
  value = getInteger(dict, "value");
  JObject *obj = getObject(dict, "tag");
  if (obj) tag = *(JArray*)obj;
}

const char* JIntegerListProperty::className() const { return "JIntegerListProperty";}
JObject* JIntegerListProperty::clone() const { return new JIntegerListProperty(*this);}

int JIntegerListProperty::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = name.compareTo(((JIntegerListProperty*)&s)->name);
  if (!result) result = value-((JIntegerListProperty*)&s)->value;
  return result;
}

JIntegerListProperty::JIntegerListProperty() {}
JIntegerListProperty::JIntegerListProperty(JString name, 
  int v, JArray _tag) : JProperty(name) {
  value = v;
  tag = _tag;
}

JString JIntegerListProperty::toJString() {
  int sz = tag.size();
  int n = max(0, min(sz-1, value));
  if (!sz) return name+"=None";
  return name+"="+*(JString*)tag[n];
}

boolean JIntegerListProperty::edit(int x, int y) {
  int ov = value;
  if (JIntegerListBox::create(JString("Property Edit for ")+
    toJString(), JMessageBox::BTN_OKCANCEL, 
    value, tag, x, y) == JMessageBox::OK) {
    check();
  }
  return (value != ov);
}