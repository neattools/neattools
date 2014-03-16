#include "JDimension.h"

char* theJDimension = JDimension().Register();
void JDimension::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "width", width);
  putInteger(os, "height", height);
}

void JDimension::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  width = getInteger(dict, "width");
  height = getInteger(dict, "height");
}

const char* JDimension::className() const { return "JDimension";}
int JDimension::hashCode() const { return (width^(height*31))&hashMask;}
JObject* JDimension::clone() const { return new JDimension(*this);}

int JDimension::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  int result = height-((JDimension*)&s)->height;
  if (!result) result = width-((JDimension*)&s)->width;
  return result;
}

JDimension::JDimension() {
  width = height = 0;
}

JDimension::JDimension(int _width, int _height) {
  width = _width;
  height = _height;
}

