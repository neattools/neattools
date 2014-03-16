#include "JTriangleButton.h"

char* theJTriangleButton = JTriangleButton().Register();
JTriangleButton* JTriangleButton::create(JComponent* p) 
{ return (JTriangleButton*)createJComponent(theJTriangleButton, p);}

const char* JTriangleButton::className() const { return "JTriangleButton";}
JObject* JTriangleButton::clone() const { return new JTriangleButton(*this);}
JTriangleButton::JTriangleButton() 
{ type = LEFT; base = 1; ratio = 1;}

int JTriangleButton::getType() { return type;}

boolean JTriangleButton::setType(int _type) {
  if (type == _type) return false;
  type = _type;
  repaint();
  return true;
}

void JTriangleButton::paint(JGraphics g) {
  JRect rect(0, 0, width, height);
  g.setJColor(getBackground());
  g.fillJRect(rect);
  g.draw3DJTriangle(rect, 
    ((state == CONCAVE) ? -depth : depth), type);
}