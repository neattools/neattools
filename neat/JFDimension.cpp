#include "JFDimension.h"
#include "JMath.h"

char* theJFDimension = JFDimension().Register();
void JFDimension::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putDouble(os, "width", width);
  putDouble(os, "height", height);
}

void JFDimension::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  width = getDouble(dict, "width");
  height = getDouble(dict, "height");
}

const char* JFDimension::className() const { return "JFDimension";}
JObject* JFDimension::clone() const { return new JFDimension(*this);}

int JFDimension::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JFDimension& obj = *(JFDimension*)&s;
  int result = cmp(height, obj.height);
  if (!result) result = cmp(width, obj.width);
  return result;
}

JFDimension::JFDimension() {
  width = height = 0;
}

JFDimension::JFDimension(double _width, double _height) {
  width = _width;
  height = _height;
}

