#include "JCanvas.h"

char* theJCanvas = JCanvas().Register();
JCanvas* JCanvas::create(JComponent* p) 
{ return (JCanvas*)createJComponent(theJCanvas, p);}

const char* JCanvas::className() const { return "JCanvas";}
JObject* JCanvas::clone() const { return new JCanvas(*this);}
JCanvas::JCanvas() { 
  state = PLAIN; depth = 0;
  base = 3; ratio = 4;
}

void JCanvas::setText(JString text) {
  JComponent::setText(text);
  repaint();
}

int JCanvas::getState() { return state;}
int JCanvas::getBState() { return (state == CONCAVE);}
int JCanvas::getDepth() { return depth;}
int JCanvas::getBase() { return base;}
int JCanvas::getRatio() { return ratio;}
boolean JCanvas::needRedraw() 
{ return (depth != 0) && (state != PLAIN);}

boolean JCanvas::setState(int _state) {
  if (state == _state) return false;
  state = _state;
  repaint();
  return true;
}

boolean JCanvas::setBState(int _bool) 
{ return setState((_bool) ? CONCAVE : CONVEX);}

boolean JCanvas::setDepth(int _depth) {
  if (depth == _depth) return false;
  depth = _depth;
  if (!depth) state = PLAIN;
  repaint();
  return true;
}

boolean JCanvas::setBaseRatio(int _base, int _ratio) {
  if ((base == _base) && (ratio == _ratio)) return false;
  base = _base; ratio = _ratio;
  repaint();
  return true;
}

void JCanvas::setJInsets(JInsets _setting)
{ setting = _setting;}

JInsets JCanvas::insets() { 
  return JInsets(setting.left+depth, 
    setting.top+depth, 
    setting.right+depth, 
    setting.bottom+depth);
}

JDimension JCanvas::preferredSize() {
  if (layoutMgr) return JComponent::preferredSize();
  int th = JFontMetrics(getJGraphics()).getHeight()/2;
  return JDimension(th*ratio+depth+depth+
    setting.left+setting.right, 
    th*base+depth+depth+
    setting.top+setting.bottom);
}

JDimension JCanvas::minimumSize() { 
  if (layoutMgr) return JComponent::minimumSize();
  int th = JFontMetrics(getJGraphics()).getHeight()/2;
  return JDimension(th*ratio+depth+depth+
    setting.left+setting.right, 
    th*base+depth+depth+
    setting.top+setting.bottom);
}

void JCanvas::paint(JGraphics g) {
  g.setJColor(getBackground());
  switch (state) {
    case CONCAVE:
      g.fill3DRect(0, 0, width, height, -depth);
      break;
    case CONVEX:
      g.fill3DRect(0, 0, width, height, depth);
      break;
    default:
      g.fillJRect(g.getClipJRect());
  }
}

