#include "JPushButton.h"

char* theJPushButton = JPushButton().Register();
JPushButton* JPushButton::create(JComponent* p, JString text) { 
  JPushButton *dest = (JPushButton*)createJComponent(theJPushButton, p);
  dest->setText(text);
  return dest;
}

const char* JPushButton::className() const { return "JPushButton";}
JObject* JPushButton::clone() const { return new JPushButton(*this);}
JPushButton::JPushButton() { autoRepeat = true;}

boolean JPushButton::getAutoRepeat() { return autoRepeat;}
boolean JPushButton::setAutoRepeat(boolean _repeat) {
  if (autoRepeat == _repeat) return false;
  autoRepeat = _repeat;
  return true;
}

boolean JPushButton::mouseDown(JEvent& e, int x, int y) {
  JButton::mouseDown(e, x, y);
  if (autoRepeat && mousePressed && 
    (getState() == CONCAVE)) {
    JEvent event(this, JEvent::ACTION_EVENT);
    postJEvent(event);
  }
  return true;
}

boolean JPushButton::mouseUp(JEvent& e, int x, int y) {
  if (mousePressed && (e.modifiers & JEvent::LBUTTON)) {
    setState(CONVEX);
    mousePressed = false;
  }
  return true;
}

