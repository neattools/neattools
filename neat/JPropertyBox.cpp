#include "JPropertyBox.h"
#include "JCanvas.h"
#include "JBorderLayout.h"
#include "JGridLayout.h"
#include "JAssociation.h"
#include "JFile.h"

char* theJPropertyBox = JPropertyBox().Register();

int JPropertyBox::create(JString text, 
  JArray properties, int& select,
  int x, int y, JModuleObj *obj) {
  int style = BTN_OKCANCEL;
  void *arg[] = {&text, &style, &properties, &select, obj};
  JPropertyBox* mb = (JPropertyBox*)createJModal(theJPropertyBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 264);
  return mb->runModal();
}

int JPropertyBox::create(JString text, 
  JArray properties, int& select,
  int x, int y) {
  int style = BTN_OKCANCEL;
  void *arg[] = {&text, &style, &properties, &select, null};
  JPropertyBox* mb = (JPropertyBox*)createJModal(theJPropertyBox, theRootWindow, arg);
  mb->setLocation(x, y, 316, 264);
  return mb->runModal();
}

const char* JPropertyBox::className() const { return "JPropertyBox";}
JObject* JPropertyBox::clone() const { return new JPropertyBox(*this);}

boolean JPropertyBox::keyDown(JEvent& e, int key) {
  switch (key) {
    case JEvent::JK_Escape: {
      endModal(CANCEL);
      break;
    }
    case JEvent::JK_Return: {
      if (pList->getSelectedIndex() > -1) 
        endModal(OK);
      break;
    }
  }
  return true;
}

boolean JPropertyBox::action(JEvent& e, JObject* arg) {
  JMessageBox::action(e, arg);
  if (e.target == pList) {
    select = pList->getSelectedIndex();
    if (!arg && (select > -1)) endModal(OK);
  }
  return true;
}

void JPropertyBox::startup() {
  JMessageBox::startup();
  JString name;
  JString &text = *(JString*)arg[0];
  JArray properties = *(JArray*)arg[2];
  select = *(int*)arg[3];
  JBorderLayout border;
  JGridLayout grid(1, 0);
  JCanvas *mainPanel = JCanvas::create(this);
  JLabel *label = JLabel::create(this, text);
  if (arg[4]) mc = JModuleCanvas::create(this, (JModuleObj*)arg[4]);
  else mc = null;
  pList = JListBox::create(this, false);
  label->setAlign(JLabel::LEFT);
  label->setBackground(JColor::cyan.darker());
  cPanel->setText("");
  cPanel->setLayout(border);
  cPanel->add(JBorderLayout::NORTH, *label);
  cPanel->add(JBorderLayout::CENTER, *pList);
  cPanel->add(JBorderLayout::SOUTH, *mainPanel);
  mainPanel->setLayout(grid);
  mainPanel->setJInsets(JInsets(0, 4, 0, 0));
  if (mc) mainPanel->add(*mc);
  for (int i=0, sz=properties.size(); i<sz; i++)
    pList->addItem(((JProperty*)properties[i])->toJString());
  ok->setText("Edit");
  cancel->setText("Exit");
}

boolean JPropertyBox::transferArguments() {
  if ((result == OK) || (result == YES))
    *(int*)arg[3] = select;
  return true;
}

boolean JPropertyBox::gotFocus(JEvent& e, JObject* arg) {
  if (e.target == this) {
    pList->requestFocus();
    pList->select(select);
    pList->setCursor(select);
  }
  return true;
}

