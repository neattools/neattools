#include "JButton.h"

char* theJButton = JButton().Register();
JButton* JButton::create(JComponent* p, JString text) { 
  JButton *dest = (JButton*)createJComponent(theJButton, p);
  dest->setText(text);
  return dest;
}

const char* JButton::className() const { return "JButton";}
JObject* JButton::clone() const { return new JButton(*this);}
JButton::JButton() { 
  mousePressed = false;
  state = CONVEX;
  depth = DEPTH;
}

boolean JButton::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
    setState(CONCAVE);
  }
  return true;
}

boolean JButton::mouseEnter(JEvent& e, int x, int y) {
  if (mousePressed) {
    setState(CONCAVE);
    return true;
  }
  return false;
}

boolean JButton::mouseExit(JEvent& e, int x, int y) {
  if (mousePressed) {
    setState(CONVEX);
    return true;
  }
  return false;
}

boolean JButton::mouseUp(JEvent& e, int x, int y) {
  if (mousePressed && (e.modifiers & JEvent::LBUTTON)) {
    if (getState() == CONCAVE) {
      setState(CONVEX);
      JEvent event(this, JEvent::ACTION_EVENT);
      postJEvent(event);
    }
    mousePressed = false;
  }
  return true;
}

