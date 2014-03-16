#include "JFocusObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JComponent.h"

char* theJFocusObj = JFocusObj().Register();
const char* JFocusObj::className() const { return "JFocusObj";}
JObject* JFocusObj::clone() const { return new JFocusObj(*this);}

JFocusObj::JFocusObj() {
  eventMask = FOCUS_MASK;
  bkgnd = JColor::yellow.darker();
}

void JFocusObj::startup() 
{ value = parent->getRoot()->isFocusOn();}

boolean JFocusObj::gotFocus(JEvent& e) { 
  setValue(mask);
  return true;
}

boolean JFocusObj::lostFocus(JEvent& e) {
  setValue(0);
  return true;
}

void JFocusObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int ovalue = value;
    link.access(JIntegerData(value));
    if (ovalue != value) 
      JComponent::theMainWindow->toFront();
  } else processColor(n, link);
}

