#include "JMessageBox.h"
#include "JCanvas.h"
#include "JSeparator.h"
#include "JBorderLayout.h"
#include "JFlowLayout.h"
#include "JLabel.h"

char* theJMessageBox = JMessageBox().Register();
int JMessageBox::create(JString text, int style, int x, int y) {
  void *arg[] = {&text, &style};
  JMessageBox* mb = (JMessageBox*)createJModal(theJMessageBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 114);
  return mb->runModal();
}

const char* JMessageBox::className() const { return "JMessageBox";}
JObject* JMessageBox::clone() const { return new JMessageBox(*this);}

void JMessageBox::setLocation(int xx, int yy, int ww, int hh) {
  if ((xx == -1) && (yy == -1)) {
    reshape(100, 100, ww, hh);
    return;
  }
  JRect rect = *theRootWindow;
  if (xx+ww > rect.width) xx = rect.width-ww;
  if (yy+hh > rect.height) yy = rect.height-hh;
  reshape(xx, yy, ww, hh);
}

void JMessageBox::startup() {
  JString &text = *(JString*)arg[0];
  int &style = *(int*)arg[1];
  JFont sfont("times", JFont::BOLD, 12);
  JBorderLayout border;
  JFlowLayout flow(JFlowLayout::CENTER, 4, 4);
  JSeparator *hSep;
  JCanvas *dPanel = JCanvas::create(this);
  JCanvas *bPanel = JCanvas::create(this);
  uPanel = JCanvas::create(this);
  hSep = JSeparator::create(this, JSeparator::HORIZONTAL);
  setJFont(sfont);
  if (theMainWindow) 
    setText(theMainWindow->getText());
  setLayout(border);
  add(JBorderLayout::CENTER, *uPanel);
  add(JBorderLayout::SOUTH, *dPanel);
  cPanel = JLabel::create(this, text);
  uPanel->setJInsets(JInsets(8));
  uPanel->setLayout(border);
  uPanel->add(JBorderLayout::CENTER, *cPanel);
  cPanel->setState(JCanvas::CONCAVE);
  cPanel->setDepth(1);
  cPanel->setJInsets(JInsets(8));
  dPanel->setLayout(border);
  dPanel->add(JBorderLayout::NORTH, *hSep);
  dPanel->add(JBorderLayout::CENTER, *bPanel);
  bPanel->setLayout(flow);
  bPanel->setJInsets(JInsets(4));
  if (style & OK) {
    ok = JButton::create(this, "Ok");
    ok->setBaseRatio(3, 8);
    bPanel->add(*ok);
  }
  if (style & YES) {
    yes = JButton::create(this, "Yes");
    yes->setBaseRatio(3, 8);
    bPanel->add(*yes);
  }
  if (style & NO) {
    no = JButton::create(this, "No");
    no->setBaseRatio(3, 8);
    bPanel->add(*no);
  }
  if (style & CANCEL) {
    cancel = JButton::create(this, "Cancel");
    cancel->setBaseRatio(3, 8);
    bPanel->add(*cancel);
  }
}

JMessageBox::JMessageBox() 
{ ok = cancel = yes = no = null;}

boolean JMessageBox::keyDown(JEvent& e, int key) {
  switch (key) {
    case JEvent::JK_Escape: {
      if (cancel) {
        e.target = cancel;
        action(e, null);
      } else endModal(CANCEL);
      break;
    }
    case JEvent::JK_Return: {
      int &style = *(int*)arg[1];
      if (style & OK) {
	e.target = ok;
        action(e, null);
      } else if (style & YES) {
	e.target = yes;
        action(e, null);
      } else endModal(OK);
      break;
    }
  }
  return true;
}

boolean JMessageBox::action(JEvent& e, JObject* arg) {
  if (ok && (e.target == ok)) {
    endModal(OK);
  } else if (cancel && (e.target == cancel)) {
    endModal(CANCEL);
  } else if (yes && (e.target == yes)) {
    endModal(YES);
  } else if (no && (e.target == no)) {
    endModal(NO);
  }
  return true;
}
