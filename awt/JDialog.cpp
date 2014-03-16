#include "JDialog.h"

char* theJDialog = JDialog().Register();
JDialog* JDialog::create(boolean widthSysMenu) 
{ return (JDialog*)createJDialog(theJDialog, theRootWindow, widthSysMenu);}

const char* JDialog::className() const { return "JDialog";}
JObject* JDialog::clone() const { return new JDialog(*this);}

JDialog::JDialog() { mousePressed = false;}

void JDialog::destroy() {
  if (theMainWindow) {
    JEvent e(this, JEvent::PEER_NOTIFY);
    theMainWindow->handleJEvent(e);
  }
  JComponent::destroy();
}

boolean JDialog::mouseEnter(JEvent& e, int _x, int _y) {
  if (theMainWindow) {
    e.arg = this;
    e.translate(x-theMainWindow->x,
      y-theMainWindow->y);
    theMainWindow->postJEvent(e);
  }
  return true;
}

boolean JDialog::mouseExit(JEvent& e, int _x, int _y) {
  if (theMainWindow) {
    e.arg = this;
    e.translate(x-theMainWindow->x,
      y-theMainWindow->y);
    theMainWindow->postJEvent(e);
  }
  return true;
}

boolean JDialog::mouseDown(JEvent& e, int _x, int _y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON) &&
    theMainWindow) {
    mousePressed = true;
    e.arg = this;
    e.translate(x-theMainWindow->x,
      y-theMainWindow->y);
    theMainWindow->postJEvent(e);
  }
  return true;
}

boolean JDialog::mouseUp(JEvent& e, int _x, int _y) {
  if ((e.modifiers & JEvent::LBUTTON) && 
    mousePressed && theMainWindow) {
    JRect rect(0, 0, width, height);
    e.arg = rect.inside(_x, _y) ? this : null;
    e.translate(x-theMainWindow->x,
      y-theMainWindow->y);
    theMainWindow->postJEvent(e);
    mousePressed = false;
  }
  return true;
}

boolean JDialog::mouseDrag(JEvent& e, int _x, int _y) {
  if (mousePressed && theMainWindow) {
    JRect rect(0, 0, width, height);
    e.arg = rect.inside(_x, _y) ? this : null;
    e.translate(x-theMainWindow->x,
      y-theMainWindow->y);
    theMainWindow->postJEvent(e);
  }
  return true;
}

boolean JDialog::keyDown(JEvent& e, int key) {
  if (mousePressed && theMainWindow) 
    theMainWindow->postJEvent(e);
  return true;
}

boolean JDialog::action(JEvent& e, JObject* arg) {
  if (theMainWindow)
    theMainWindow->postJEvent(e);
  return true;
}

