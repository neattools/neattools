#include "JIntegerListBox.h"
#include "JBorderLayout.h"
#include "JInteger.h"

char* theJIntegerListBox = JIntegerListBox().Register();
int JIntegerListBox::create(JString text, int style, int& value, 
  JArray tag, int x, int y) {
  void *arg[] = {&text, &style, &value, &tag};
  JIntegerListBox* mb = (JIntegerListBox*)createJModal(
    theJIntegerListBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 214);
  return mb->runModal();
}

const char* JIntegerListBox::className() const { return "JIntegerListBox";}
JObject* JIntegerListBox::clone() const { return new JIntegerListBox(*this);}

void JIntegerListBox::startup() {
  JMessageBox::startup();
  JString &text = *(JString*)arg[0];
  JArray &tag = *(JArray*)arg[3];
  value = *(int*)arg[2];
  JBorderLayout border;
  JLabel *label = JLabel::create(this, text);
  tagList = JListBox::create(this, false);
  int i, sz;
  for (i=0, sz=tag.size(); i<sz; i++)
    tagList->addItem(*(JString*)tag[i]);
  value = max(0, min(sz-1, value));
  label->setAlign(JLabel::LEFT);
  label->setBackground(JColor::cyan.darker());
  cPanel->setText("");
  cPanel->setLayout(border);
  cPanel->add(JBorderLayout::NORTH, *label);
  cPanel->add(JBorderLayout::CENTER, *tagList);
}

boolean JIntegerListBox::transferArguments() {
  if ((result == OK) || (result == YES))
    *(int*)arg[2] = value;
  return true;
}

boolean JIntegerListBox::action(JEvent& e, JObject* arg) {
  JMessageBox::action(e, arg);
  if (e.target == tagList) {
    value = tagList->getSelectedIndex();
    if (!arg && (value > -1)) endModal(OK);
  }
  return true;
}

boolean JIntegerListBox::gotFocus(JEvent& e, JObject* arg) {
  if (tagList && (e.target == this)) {
    tagList->requestFocus();
    tagList->select(value);
    tagList->setCursor(value);
  }
  return true;
}

