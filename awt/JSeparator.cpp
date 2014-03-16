#include "JSeparator.h"

char* theJSeparator = JSeparator().Register();
JSeparator* JSeparator::create(JComponent* p, int _type) { 
  JSeparator *dest = (JSeparator*)createJComponent(theJSeparator, p);
  dest->setType(_type);
  return dest;
}

const char* JSeparator::className() const { return "JSeparator";}
JObject* JSeparator::clone() const { return new JSeparator(*this);}
JSeparator::JSeparator() {
  state = CONCAVE;
  depth = 1;
  base = ratio = 0;
}

int JSeparator::getType() { return type;}

boolean JSeparator::setType(int _type) {
  if (type == _type) return false;
  type = _type;
  return true;
}

boolean JSeparator::needRedraw() { return true;}