#include "JControlObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JIntegerData.h"

char* theJControlObj = JControlObj().Register();
const char* JControlObj::className() const { return "JControlObj";}
JObject* JControlObj::clone() const { return new JControlObj(*this);}

void JControlObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dx = w/5;
  int bx = (w-dx*3)/2;
  int kx = max(3, w/15);
  int sx = kx/2;
  int my = h/2;
  g.drawLine(x+bx, y+my, x+bx+dx, y+my);
  g.drawLine(x+bx+dx*2, y+my, x+bx+dx*3, y+my);
  g.fillOval(x+bx+dx-sx, y+my-sx, kx, kx);
  g.fillOval(x+bx+dx*2-sx, y+my-sx, kx, kx);
  if (control) g.drawLine(x+bx+dx, y+my, x+bx+dx*2, y+my);
}

void JControlObj::engine(int n, JLinkObj& link) {
  if (n == IN_N) {
    JSampleObj::engine(n, link);
  } else if (n == IN_CONTROL) {
    int oldv = control;
    link.access(JIntegerData(control));
    control = (control != 0);
    if (control != oldv) {
      repaint();
      for (int i=0; i<N; i++)
        broadcast(i);
    }
  } else if (control) broadcast(n-IN_LAST);
}

