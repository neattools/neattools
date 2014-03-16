#include "JNeatTool.h"
#include "JAbout.h"

char* theJNeatTool = JNeatTool().Register();
const char* JNeatTool::className() const { return "JMainWindow";}
JObject* JNeatTool::clone() const { return new JNeatTool(*this);}
JNeatTool::JNeatTool() { view = null;}

void JNeatTool::startup() {
  theMainWindow = this;
  JFont font("times", JFont::BOLD, 16);
  setForeground(JColor::black);
  setBackground(JColor::lightGray);
  setJFont(font);
  setText("NeatTools");
  view = JView::create(this);
  if ((x <= 1) || (y <= 1)) {
    JRect rect = *theRootWindow;
    rect.x = rect.width/16;
    rect.width = rect.width-rect.x-rect.x;
    rect.y = rect.height/16;
    rect.height = rect.height-rect.y-rect.y;
    reshape(rect);
  }
  JAbout::create();
}

void JNeatTool::destroy() {
  if (JAbout::about) JAbout::about->dispose();
  JWindow::destroy();
}

void JNeatTool::activate() 
{ if (view) view->activate();}

void JNeatTool::deactivate() 
{ if (view) view->deactivate();}

void JNeatTool::layoutMinimized() 
{ if (view) view->layoutMinimized();}

void JNeatTool::layoutRestored() 
{ if (view) view->layoutRestored();}


boolean JNeatTool::handleJEvent(JEvent& e) {
  switch (e.id) {
    case JEvent::CHILD_NOTIFY:
      view = null;
    case JEvent::GOT_FOCUS:
    case JEvent::LOST_FOCUS:
    case JEvent::PARENT_NOTIFY:
      return JWindow::handleJEvent(e);
    case JEvent::MOUSE_DOWN:
    case JEvent::MOUSE_UP:
    case JEvent::MOUSE_MOVE:
    case JEvent::MOUSE_ENTER:
    case JEvent::MOUSE_EXIT:
    case JEvent::MOUSE_DRAG:
    case JEvent::MOUSE_ACTION:
      if (view)	translateJEvent(e, view);
      break;
  }
  boolean result = false;
  if (view) result = view->handleJEvent(e);
  else result = JWindow::handleJEvent(e);
  return result;
}

boolean JNeatTool::gotFocus(JEvent& e, JObject* arg) {
  if (view) view->requestFocus();
  return true;
}

#include "JWindow.hpp"

#if defined(WIN32)

  int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpszCmdLine, int nCmdShow) {
    JMicroSoft JMS(hInstance, hPrevInstance, lpszCmdLine, nCmdShow);
    JMS.MessageLoop();
    return 0;
  }

#else

  int main(int argc, char** argv) {
    JUNIX junix(argc, argv);
    junix.MessageLoop();
    return null;
  }

#endif

