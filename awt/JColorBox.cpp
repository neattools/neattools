#include "JColorBox.h"
#include "JLabel.h"
#include "JBorderLayout.h"
#include "JGridLayout.h"
#include "JInteger.h"

char* theJColorBox = JColorBox().Register();
int JColorBox::create(JString text, int style, JColor& c, int x, int y) {
  void *arg[] = {&text, &style, &c};
  JColorBox* mb = (JColorBox*)createJModal(theJColorBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 214);
  return mb->runModal();
}

const char* JColorBox::className() const { return "JColorBox";}
JObject* JColorBox::clone() const { return new JColorBox(*this);}

void JColorBox::startup() {
  JMessageBox::startup();
  JString &text = *(JString*)arg[0];
  JColor &c = *(JColor*)arg[2];
  JBorderLayout border;
  JGridLayout grid(1, 1);
  JGridLayout grid2(0, 1, 0, 4);
  JLabel *label = JLabel::create(this, text);
  JCanvas *sPanel = JCanvas::create(this);
  JCanvas *mPanel = JCanvas::create(this);
  rs = JScroller::create(this, JScroller::HORIZONTAL);
  gs = JScroller::create(this, JScroller::HORIZONTAL);
  bs = JScroller::create(this, JScroller::HORIZONTAL);
  rs->setValue(c.getRed(), 1, 0, 256, false);
  gs->setValue(c.getGreen(), 1, 0, 256, false);
  bs->setValue(c.getBlue(), 1, 0, 256, false);
  canvas = JLabel::create(this, "");
  canvas->setBackground(c);
  label->setAlign(JLabel::LEFT);
  label->setBackground(JColor::cyan.darker());
  cPanel->setText("");
  cPanel->setLayout(border);
  cPanel->add(JBorderLayout::NORTH, *label);
  cPanel->add(JBorderLayout::CENTER, *mPanel);
  cPanel->add(JBorderLayout::SOUTH, *sPanel);
  mPanel->setLayout(grid);
  mPanel->setJInsets(JInsets(4, 4, 4, 4));
  mPanel->setState(JCanvas::CONCAVE);
  mPanel->setDepth(1);
  mPanel->add(*canvas);
  sPanel->setLayout(grid2);
  sPanel->setJInsets(JInsets(0, 4, 0, 0));
  sPanel->add(*rs);
  sPanel->add(*gs);
  sPanel->add(*bs);
}

boolean JColorBox::transferArguments() {
  if ((result == OK) || (result == YES))
    *(JColor*)arg[2] = JColor(rs->getValue(),
      gs->getValue(), bs->getValue());
  return true;
}

boolean JColorBox::action(JEvent& e, JObject* arg) {
  JMessageBox::action(e, arg);
  if ((e.target == rs) || (e.target == gs) ||
    (e.target == bs)) {
    canvas->setBackground(JColor(rs->getValue(),
      gs->getValue(), bs->getValue()));
    canvas->setText(JString("(")+
      JInteger::toJString(rs->getValue())+","+
      JInteger::toJString(gs->getValue())+","+
      JInteger::toJString(bs->getValue())+")");
  }
  return true;
}