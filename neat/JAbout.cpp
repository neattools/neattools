#include "JAbout.h"

char* theJAbout = JAbout().Register();
JAbout* JAbout::about = null;
JAbout* JAbout::create() 
{ return (about = (JAbout*)createJModal(theJAbout, theRootWindow));}
const char* JAbout::className() const { return "JAbout";}
JObject* JAbout::clone() const { return new JAbout(*this);}
JAbout::JAbout() { 
  depth = 2;
  state = CONVEX;
}

void JAbout::startup() {
  int w, dx;
  int h = theRootWindow->height/4;
  int dy = (theRootWindow->height-h)/2;
  char *name = "NeatTools V1.2";
  JFont font("courier", JFont::BOLD_ITALIC, h*2/3);
  setJFont(font);
  setText(name);
  JFontMetrics fm(getJGraphics());
  w = fm.stringWidth(name)+80;
  dx = (theRootWindow->width-w)/2;
  setBackground(JColor::green.darker());
  reshape(dx, dy, w, h);
  setResizable(false);
  setMousePos(dx+w/2, dy+h/2);
  show();
}

boolean JAbout::keyDown(JEvent& e, int key) {
  switch (key) {
    case JEvent::JK_Escape:
    case JEvent::JK_Return:
    case JEvent::JK_space:
      dispose();
	  about = null;
      break;
  }
  return true;
}

boolean JAbout::mouseUp(JEvent& e, int x, int y) {
  dispose();
  about = null;
  return true;
}

boolean JAbout::mouseExit(JEvent& e, int x, int y) {
  dispose();
  about = null;
  return true;
}

void JAbout::paint(JGraphics g) {
  JCanvas::paint(g);
  int delta = 20;
  JRect rect(0, 0, width, height);
  g.draw3DJRect(rect.shrink(delta, delta), -depth);
  JString text = getText();
  if (text.length()) {
    JFontMetrics fm(g);
    int dx, dy;
    JColor c[14] = { 
      JColor::red, JColor::white, 
      JColor::magenta.darker(), JColor::yellow,
      JColor::orange, JColor::blue,
      JColor::pink, JColor::magenta,
      JColor::orange,
	  JColor::green.darker(),
	  JColor::blue,
	  JColor::magenta.darker(),
	  JColor::blue,
	  JColor::yellow };
    dy = (height-fm.getHeight())/2;
    dx = (width-fm.stringWidth(text))/2;
    g.setJColor(getBackground().brighter());
    g.drawJString(text, dx+1, dy+1);
    g.setJColor(getBackground().darker());
    g.drawJString(text, dx-1, dy-1);
    for (int i=0; i<14; i++) {
      JString ch = text(i, i+1);
      g.setJColor(c[i]);
      g.drawJString(ch, dx, dy);
      dx += fm.stringWidth(ch);
    }
  }
}

boolean JAbout::gotFocus(JEvent& e, JObject* arg) {
  return true;
}

