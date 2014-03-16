#include "JToggleButton.h"

char* theJToggleButton = JToggleButton().Register();
JToggleButton* JToggleButton::create(JComponent *p, JString text, int state) { 
  JToggleButton *dest = (JToggleButton*)createJComponent(theJToggleButton, p);
  dest->setState(state);
  dest->setText(text);
  return dest;
}

const char* JToggleButton::className() const { return "JToggleButton";}
JObject* JToggleButton::clone() const { return new JToggleButton(*this);}
JToggleButton::JToggleButton() {}

boolean JToggleButton::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
  }
  return true;
}

boolean JToggleButton::mouseUp(JEvent& e, int x, int y) {
  if (mousePressed && (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = false;
    JEvent event(this, JEvent::ACTION_EVENT
      , 0, 0, (state == CONCAVE) ? CONVEX : CONCAVE, 0);
    postJEvent(event);
  }
  return true;
}

