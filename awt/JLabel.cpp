#include "JLabel.h"
#include "JBlock.h"

char* theJLabel = JLabel().Register();
JLabel* JLabel::create(JComponent* p, JString text, boolean password) { 
  JLabel *dest = (JLabel*)createJComponent(theJLabel, p);
  dest->setText(text);
  dest->setPasswordMode(password);
  return dest;
}

const char* JLabel::className() const { return "JLabel";}
JObject* JLabel::clone() const { return new JLabel(*this);}
JLabel::JLabel() {
  raise = AUTO; 
  align = CENTER;
  scale = scaleTotal = 0;
  passwordMode = false;
}

int JLabel::getAlign() { return align;}
int JLabel::getRaise() { return raise;}

boolean JLabel::setRaise(int _raise) {
  if (raise == _raise) return false;
  raise = _raise;
  repaint();
  return true;
}

boolean JLabel::setAlign(int _align) {
  if (align == _align) return false;
  align = _align;
  repaint();
  return true;
}

boolean JLabel::setScaleTotal(int _total) {
  if (scaleTotal == _total) return false;
  scaleTotal = _total;
  scale = 0;
  repaint(true);
  return true;
}

boolean JLabel::setScale(int _scale) {
  if (scale == _scale) return false;
  scale = _scale;
  if (scale == scaleTotal)
    scale = scaleTotal = 0;
  repaint(true);
  return true;
}

void JLabel::setPasswordMode(boolean mode) {
  passwordMode = mode;
}

JRect JLabel::formatText(JGraphics g, JString text,
  JRect rect, JColor color, JColor bkgnd, 
  int raise, int align) {
  int len = text.length();
  JFontMetrics fm(g);
  int dx, dy;
  int sw = fm.stringWidth(text);
  int sh = fm.getHeight();
  while (sw > rect.width) {
    text = text(0, --len);
    sw = fm.stringWidth(text);
    if (!len) break;
  }
  dy = rect.y+(rect.height-sh)/2;
  switch (align) {
    case LEFT:
      dx = rect.x;
      break;
    case RIGHT:
      dx = rect.x+rect.width-sw;
      break;
    default:
      dx = rect.x+(rect.width-sw)/2;
  }
  if (len > 0) {
    switch (raise) {
      case CONCAVE:
        g.setJColor(bkgnd.brighter());
        g.drawJString(text, dx+1, dy+1);
        break;
      case CONVEX:
        g.setJColor(bkgnd.brighter());
        g.drawJString(text, dx-1, dy-1);
        break;
    }
    g.setJColor(color);
    g.drawJString(text, dx, dy);
  }
  return JRect(dx, dy, sw, len);
}

void JLabel::paint(JGraphics g) {
  JCanvas::paint(g);
  if (scaleTotal > 0) {
    int tx = width-depth*2;
    int ty = height-depth*2;
    int sx = tx*scale/(scaleTotal-1);
    g.setJColor(JColor(0, 128, 128));
    g.fillRect(depth, depth, sx, ty);
    return;
  }
  JRect rect(depth*2, depth*2, width-depth*4, height-depth*4);
  int mode = raise;
  if (mode == AUTO) {
    switch (state) {
      case CONCAVE: mode = CONVEX; break;
      case CONVEX: mode = CONCAVE; break;
      default: mode = PLAIN;
    }
  }
  JString dest = text;
  if (passwordMode) {
    JBlock buf(text.length(), '*');
    dest = JString(buf);
  }
  formatText(g, dest, rect,
    getForeground(), getBackground(),
    mode, align);
}

boolean JLabel::needRedraw() { return true;}
