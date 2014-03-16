#include "JWindow.h"

char* theJWindow = JWindow().Register();
JWindow* JWindow::create() 
{ return (JWindow*)createJWindow(theJWindow, theRootWindow);}

const char* JWindow::className() const { return "JWindow";}
JObject* JWindow::clone() const { return new JWindow(*this);}
