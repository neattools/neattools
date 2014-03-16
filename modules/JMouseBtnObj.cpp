#include "JMouseBtnObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JCharacter.h"
#include "JComponent.h"

char* theJMouseBtnObj = JMouseBtnObj().Register();
void JMouseBtnObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "type", type);
  putInteger(os, "mask", tmask);
}

void JMouseBtnObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  type = getInteger(dict, "type");
  tmask = getInteger(dict, "mask");
}

const char* JMouseBtnObj::className() const { return "JMouseBtnObj";}
JObject* JMouseBtnObj::clone() const { return new JMouseBtnObj(*this);}

JMouseBtnObj::JMouseBtnObj(int _type) {
  eventMask = FOCUS_MASK | GLOBAL_MOUSE_MASK;
  igm = 2;
  type = _type;
  state = 0;
  focusOn = true;
  switch (type) {
    case LEFT: tmask = JEvent::LBUTTON; break;
    case RIGHT: tmask = JEvent::RBUTTON; break;
    case MIDDLE: tmask = JEvent::MBUTTON; break;
    default: tmask = null;
  }
}

void JMouseBtnObj::startup()
{ focusOn = parent->getRoot()->isFocusOn();}

void JMouseBtnObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  switch (type) {
    case LEFT:
      drawText(g, "LBtn", rect);
      break;
    case RIGHT:
      drawText(g, "RBtn", rect);
      break;
    case MIDDLE:
      drawText(g, "MBtn", rect);
      break;
  }
}

boolean JMouseBtnObj::inputAllowed(int n)
{ return true;}

JString JMouseBtnObj::inputTag(int n) { 
  char* tag[] = { "click(logical)", "depress(logical)"};
  return tag[n];
}

boolean JMouseBtnObj::gotFocus(JEvent& e) 
{ focusOn = true; return true;}
boolean JMouseBtnObj::lostFocus(JEvent& e) 
{ focusOn = false; return true;}

boolean JMouseBtnObj::globalMouseDown(JEvent& e, int x, int y) {
  if (e.modifiers & tmask) {
    value = mask;
    broadcast(0);
  }
  return true;
}

boolean JMouseBtnObj::globalMouseUp(JEvent& e, int x, int y) {
  if (e.modifiers & tmask) {
    value = 0;
    broadcast(0);
  }
  return true;
}

#if defined(WIN32)
  #include <windows.h>
#endif

void JMouseBtnObj::engine(int n, JLinkObj& link) {
  if (focusOn) return;
#if defined(WIN32)
  POINT pt;
  GetCursorPos(&pt);
  if (JComponent::getJComponent((int)WindowFromPoint(pt))) return;
  if (!n) {
    int click;
    link.access(JIntegerData(click));
    if (click && !state) {
      switch (type) {
        case LEFT:
          mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0L, 0L);
	  break;
        case RIGHT:
          mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0L, 0L);
	  break;
        case MIDDLE:
          mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0L, 0L);
          mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0L, 0L);
	  break;
      }
    }
  } else {
    int olds = state;
    link.access(JIntegerData(state));
    state = (state != 0) ? mask : 0;
    if (state != olds) {
      switch (type) {
        case LEFT:
          mouse_event(
	    (state) ? MOUSEEVENTF_LEFTDOWN : 
	    MOUSEEVENTF_LEFTUP, 
	    0, 0, 0L, 0L);
	  break;
        case RIGHT:
          mouse_event(
	    (state) ? MOUSEEVENTF_RIGHTDOWN : 
	    MOUSEEVENTF_RIGHTUP, 
	    0, 0, 0L, 0L);
	  break;
        case MIDDLE:
          mouse_event(
	    (state) ? MOUSEEVENTF_MIDDLEDOWN : 
	    MOUSEEVENTF_MIDDLEUP, 
	    0, 0, 0L, 0L);
	  break;
      }
    }
  }
#endif
}

void JMouseBtnObj::addButton(JComponent* panel) { 
  addModuleButton(panel, JMouseBtnObj(LEFT));
  addModuleButton(panel, JMouseBtnObj(RIGHT));
  addModuleButton(panel, JMouseBtnObj(MIDDLE));
}
