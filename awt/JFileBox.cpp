#include "JFileBox.h"
#include "JCanvas.h"
#include "JBorderLayout.h"
#include "JGridLayout.h"
#include "JAssociation.h"
#include "JFile.h"
#include "JFile.hpp"

char* theJFileBox = JFileBox().Register();
int JFileBox::create(JString text, 
  JString& data, JString type, int x, int y) {
  int style = BTN_OKCANCEL;
  void *arg[] = {&text, &style, &data, &type};
  JString cwd = JFile::getCurrentDirectory();
  JFileBox* mb = (JFileBox*)createJModal(theJFileBox, theRootWindow, arg);
  mb->setLocation(x, y, 366, 314);
  int result = (mb) ? mb->runModal() : CANCEL;
  JFile::setCurrentDirectory(cwd);
  return result;
}

const char* JFileBox::className() const { return "JFileBox";}
JObject* JFileBox::clone() const { return new JFileBox(*this);}

boolean JFileBox::action(JEvent& e, JObject* arg) {
  if (!tf) return true;
  if (e.target == ok) {
    int p;
    JString name = tf->getText().trim();
    if (!name.length()) {
      tf->setText(name);
      return true;
    }
#if defined(WIN32)
    p = name.lastIndexOf(':');
    if ((p > -1) && (name[p+1] != JFile::separator[0]))
      name+=JFile::separator;
#endif
    p = name.lastIndexOf(JFile::separator[0]);
    if (p > -1) {
      JFile dir(name(0, p+1));
      if (dir.isDirectory()) path = dir;
      name = name(p+1);
    }
    if ((name.indexOf('*') > -1) ||
      (name.indexOf('?') > -1)) {
      type = name;
    } else {
      JFile file(path, name);
      if (!file.isDirectory()) {
        if (name.indexOf('.') == -1)
	  name += ext;
	tf->setText(name);
        endModal(OK);
	return true;
      }
      path = file;
    }
    tf->setText("");
    updateLists();
  } else if (e.target == cancel) {
    endModal(CANCEL);
  } else if (e.target == fileList) {
    if (arg) {
      tf->setText(*(JString*)((JAssociation*)arg)->key());
    } else {
      JListBox *list = (JListBox*)e.target;
      if (list->getSelectedIndex() > -1) {
        tf->setText(list->getSelectedItem());
        endModal(OK);
      }
    }
  } else if (e.target == dirList) {
    if (arg) {
    } else {
      JListBox *list = (JListBox*)e.target;
      if (list->getSelectedIndex() > -1) {
        JString dir = list->getSelectedItem();
        dir = dir(1, dir.length()-1);
	if (dir[0] == '-') {
#if defined(WIN32)
          char cwd[MAXPATHLEN];
          if (_getdcwd(dir[1]-'A'+1, cwd, MAXPATHLEN))
	    path = JFile(JString(cwd, JString::needCopy));
	  else path = JFile(dir(1, 2)+":\\");
#endif
	} else if (dir[0] == '.') {
          path = JFile(path.getParent());
        } else path = JFile(path.getPath()+dir);
        updateLists();
      }
    }
  }
  return true;
}

void JFileBox::startup() {
  JMessageBox::startup();
  JString name;
  JString &text = *(JString*)arg[0];
  JFile file = JFile(*(JString*)arg[2]);
  type = *(JString*)arg[3];
  ext = type(1);
  if (file.isDirectory()) {
    path = file.getPath();
  } else {
    path = file.getParent();
    name = file.getName();
  }
  JBorderLayout border;
  JGridLayout grid(1, 0, 8, 8);
  JGridLayout grid2(0, 1);
  JCanvas *listPanel = JCanvas::create(this);
  JCanvas *mainPanel = JCanvas::create(this);
  JLabel *label = JLabel::create(this, text);
  tf = JTextField::create(this, name, 256);
  filter = JLabel::create(this, "");
  dirList = JListBox::create(this, false);
  fileList = JListBox::create(this, false);
  label->setAlign(JLabel::LEFT);
  label->setBackground(JColor::cyan.darker());
  filter->setAlign(JLabel::LEFT);
  filter->setBackground(JColor::gray);
  cPanel->setText("");
  cPanel->setLayout(border);
  cPanel->add(JBorderLayout::NORTH, *mainPanel);
  cPanel->add(JBorderLayout::CENTER, *listPanel);
  cPanel->add(JBorderLayout::SOUTH, *filter);
  listPanel->setJInsets(JInsets(0, 8, 0, 8));
  listPanel->setLayout(grid);
  listPanel->add(*dirList);
  listPanel->add(*fileList);
  mainPanel->setLayout(grid2);
  mainPanel->add(*label);
  mainPanel->add(*tf);
  updateLists();
}

boolean JFileBox::transferArguments() {
  if (tf && ((result == OK) || (result == YES))) {
    JString dire = path.getPath();
    JString work = JFile::workDir.getPath();
    if (dire.indexOf(work) > -1)
      dire = dire(work.length());
    *(JString*)arg[2] = dire+tf->getText();
  }
  return true;
}

void JFileBox::updateLists() {
  int i, sz;
  if (path.isDirectory())
    JFile::setCurrentDirectory(path.getPath());
  JArray list = path.list(JFile::LA_DIRECTORY |
    JFile::LA_DRIVE | JFile::LA_SORT);
  dirList->clear();
  for (i=0, sz=list.size(); i<sz; i++)
    dirList->addItem(*(JString*)list[i]);
  dirList->resetScroller();
  list = path.list(JFile::LA_FILE | JFile::LA_SORT, type);
  fileList->clear();
  for (i=0, sz=list.size(); i<sz; i++)
    fileList->addItem(*(JString*)list[i]);
  fileList->resetScroller();
  dirList->repaint();
  fileList->repaint();
  filter->setText(path.getPath()+type);
}

