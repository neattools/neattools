#include "JInsets.h"

char* theJInsets = JInsets().Register();
void JInsets::writeContent(JOutputStream& os) {
  JObject::writeContent(os);
  putInteger(os, "left", left);
  putInteger(os, "top", top);
  putInteger(os, "right", right);
  putInteger(os, "bottom", bottom);
}

void JInsets::readContent(JDictionary& dict) {
  JObject::readContent(dict);
  left = getInteger(dict, "left");
  top = getInteger(dict, "top");
  right = getInteger(dict, "right");
  bottom = getInteger(dict, "bottom");
}

const char* JInsets::className() const { return "JInsets";}
int JInsets::hashCode() const
{ return (left^(top*31)^(right*23)^(bottom*29))&hashMask;}
JObject* JInsets::clone() const { return new JInsets(*this);}

int JInsets::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JInsets &obj = *(JInsets*)&s;
  int result = top-obj.top;
  if (!result) {
    result = bottom-obj.bottom;
    if (!result) {
      result = left-obj.left;
      if (!result) result = right-obj.right;
    }
  }
  return result;
}

JInsets::JInsets() { left = top = right = bottom = 0;}

JInsets::JInsets(int thickness) 
{ left = top = right = bottom = thickness;}

JInsets::JInsets(int _left, int _top, int _right, int _bottom) {
  left = _left;
  top = _top;
  right = _right;
  bottom = _bottom;
}


