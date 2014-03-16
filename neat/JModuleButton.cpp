#include "JModuleButton.h"

char* theJModuleButton = JModuleButton().Register();
JModuleButton* JModuleButton::create(JComponent *p, const JModuleObj& obj) { 
  JModuleButton *dest = (JModuleButton*)createJComponent(theJModuleButton, p);
  dest->pmodule = (JModuleObj*)obj.clone();
  dest->pmodule->reshape(0, 0, 1, 1);
  return dest;
}

const char* JModuleButton::className() const { return "JModuleButton";}
JObject* JModuleButton::clone() const { return new JModuleButton(*this);}
JModuleButton::JModuleButton() 
{ base = 6; ratio = 6; pmodule = null;}

void JModuleButton::startup() 
{ setBackground(JColor::cyan.darker());}

void JModuleButton::destroy() { 
  JButton::destroy();
  delete pmodule;
}

void JModuleButton::paint(JGraphics g) {
  if (!width || !pmodule) return;
  double scale = ((double)width)/pmodule->width;
  JRect rect(0, 0, width, height);
  JRect inner = rect.shrink(depth, depth);
  JRegion rgn(inner);
  JRegion clip = rgn;
  g.setJColor(pmodule->getModuleColor());
  g.draw3DJRect(rect,
    (state == CONVEX) ? depth : -depth);
  g.setJRegion(rgn);
  g.fillJRect(inner);
  pmodule->update(g, 0, 0, rgn, scale);
}

boolean JModuleButton::mouseDown(JEvent& e, int x, int y) {
  if ((e.id == JEvent::MOUSE_DOWN) &&
    (e.modifiers & JEvent::LBUTTON)) {
    mousePressed = true;
    setState(CONCAVE);
  }
  return false;
}

boolean JModuleButton::mouseUp(JEvent& e, int x, int y) {
  if (mousePressed && (e.modifiers & JEvent::LBUTTON)) {
    if (getState() == CONCAVE) {
      setState(CONVEX);
      JEvent event(this, JEvent::ACTION_EVENT, pmodule);
      postJEvent(event);
    }
    mousePressed = false;
  }
  return false;
}

