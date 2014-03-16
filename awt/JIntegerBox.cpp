#include "JIntegerBox.h"
#include "JBorderLayout.h"
#include "JInteger.h"

char* theJIntegerBox = JIntegerBox().Register();
int JIntegerBox::create(JString text, int style, int& value, 
  int min, int max, int x, int y) {
  JString data = JInteger::toJString(value);
  boolean password = false;
  void *arg[] = {&text, &style, &data, &password, &value, &min, &max};
  JIntegerBox* mb = (JIntegerBox*)createJModal("JIntegerBox", theRootWindow, arg);
  mb->setLocation(x, y, 316, 124);
  return mb->runModal();
}

const char* JIntegerBox::className() const { return "JIntegerBox";}
JObject* JIntegerBox::clone() const { return new JIntegerBox(*this);}

void JIntegerBox::startup() {
  JInputBox::startup();
  int &value = *(int*)arg[4];
  int &min = *(int*)arg[5];
  int &max = *(int*)arg[6];
  scroller = JScroller::create(this, JScroller::HORIZONTAL);
  scroller->setValue(value, 1, min, max+1, false);
  cPanel->add(JBorderLayout::SOUTH, *scroller);
  reshape(x, y, width, height+
    scroller->preferredSize().height);
}

boolean JIntegerBox::transferArguments() {
  if (tf && ((result == OK) || (result == YES)))
    *(int*)arg[4] = (int)JInteger(tf->getText());
  return true;
}

boolean JIntegerBox::action(JEvent& e, JObject* arg) {
  JInputBox::action(e, arg);
  if (tf && (e.target == scroller))
    tf->setText(JInteger::toJString(e.key));
  return true;
}