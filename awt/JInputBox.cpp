#include "JInputBox.h"
#include "JCanvas.h"
#include "JBorderLayout.h"

char* theJInputBox = JInputBox().Register();
int JInputBox::create(JString text, int style, JString& data,
  int x, int y, boolean password) {
  void *arg[] = {&text, &style, &data, &password};
  JInputBox* mb = (JInputBox*)createJModal(theJInputBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 114);
  return mb->runModal();
}

const char* JInputBox::className() const { return "JInputBox";}
JObject* JInputBox::clone() const { return new JInputBox(*this);}

void JInputBox::startup() {
  JMessageBox::startup();
  JString &text = *(JString*)arg[0];
  JString &data = *(JString*)arg[2];
  boolean &password = *(boolean*)arg[3];
  JBorderLayout border;
  JLabel *label = JLabel::create(this, text);
  tf = JTextField::create(this, data, 256, password);
  label->setAlign(JLabel::LEFT);
  label->setBackground(JColor::cyan.darker());
  cPanel->setText("");
  cPanel->setLayout(border);
  cPanel->add(JBorderLayout::NORTH, *label);
  cPanel->add(JBorderLayout::CENTER, *tf);
}

boolean JInputBox::gotFocus(JEvent& e, JObject* arg) {
  if (tf && (e.target == this)) tf->requestFocus();
  return true;
}

boolean JInputBox::transferArguments() {
  if (tf && ((result == OK) || (result == YES)))
    *(JString*)arg[2] = tf->getText();
  return true;
}

