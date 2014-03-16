#include "JMousePosObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JCharacter.h"

char* theJMousePosObj = JMousePosObj().Register();
const char* JMousePosObj::className() const { return "JMousePosObj";}
JObject* JMousePosObj::clone() const { return new JMousePosObj(*this);}
JMousePosObj::JMousePosObj(int _type) :JMouseBtnObj(_type) {}

void JMousePosObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  switch (type) {
    case XPOS:
      drawText(g, "MsX", rect);
      break;
    case YPOS:
      drawText(g, "MsY", rect);
      break;
  }
}

boolean JMousePosObj::outputAllowed(int n) { return true;}

JString JMousePosObj::inputTag(int n) { 
  char* tag[] = { "position", "delta"};
  if (!n) return JString(tag[n])+NBTag();
  return tag[n];
}

boolean JMousePosObj::globalMouseDown(JEvent& e, int x, int y) { return true;}
boolean JMousePosObj::globalMouseUp(JEvent& e, int x, int y) { return true;}

boolean JMousePosObj::globalMouseMove(JEvent& e, int x, int y) {
  switch (type) {
    case XPOS: {
      value = x*mask/(JComponent::theRootWindow->width-1);
      break;
    }
    case YPOS: {
      value = y*mask/(JComponent::theRootWindow->height-1);
      break;
    }
  }
  broadcast(0);
  return true;
}

#if defined(WIN32)
  #include <windows.h>
#endif

void JMousePosObj::engine(int n, JLinkObj& link) {
  if (focusOn) return;
  if (!n) {
    int newPos;
    link.access(JIntegerData(newPos));
    newPos = max(0, min(mask, newPos));
#if defined(WIN32)
    POINT pt;
    GetCursorPos(&pt);
    switch (type) {
      case XPOS: {
	SetCursorPos(newPos*(JComponent::theRootWindow->width-1)/mask, pt.y);
        break;
      } 
      case YPOS: {
	SetCursorPos(pt.x, newPos*(JComponent::theRootWindow->height-1)/mask);
        break;
      }
    }
#endif
  } else {
    int delta;
    link.access(JIntegerData(delta));
    if (delta) {
#if defined(WIN32)
      POINT pt;
      GetCursorPos(&pt);
      switch (type) {
        case XPOS:
	  SetCursorPos(pt.x+delta, pt.y);
          break;
        case YPOS:
	  SetCursorPos(pt.x, pt.y+delta);
          break;
      }
#endif
    }
  }
}

void JMousePosObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JMousePosObj(XPOS));
  addModuleButton(panel, JMousePosObj(YPOS));
}
