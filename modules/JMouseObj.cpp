#include "JMouseObj.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JCharacter.h"
#include "JComponent.h"

char* theJMouseObj = JMouseObj().Register();

const char* JMouseObj::className() const { return "JMouseObj";}
JObject* JMouseObj::clone() const { return new JMouseObj(*this);}

JMouseObj::JMouseObj() {
  eventMask = FOCUS_MASK | GLOBAL_MOUSE_MASK | GLOBAL_KEYBOARD_MASK;
  igm = _LAST+_LAST-2;
  ogm = _LAST;
  focusOn = true;
  for (int i=0; i<_LAST; i++) state[i] = 0;
}

void JMouseObj::startup()
{ focusOn = parent->getRoot()->isFocusOn();}

void JMouseObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, "Ms", rect);
}

void JMouseObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = state[n];}
boolean JMouseObj::inputAllowed(int n)
{ return true;}

JString JMouseObj::inputTag(int n) { 
  char* tag[] = { 
    "xpos-absolute", 
    "ypos-absolute", 
    "lbtn-click(logical)", 
    "mbtn-click(logical)", 
    "rbtn-click(logical)", 
    "xpos-delta", 
    "ypos-delta", 
    "lbtn-depress(logical)",
    "mbtn-depress(logical)",
    "rbtn-depress(logical)",
    "wheelForward(logical)",
    "wheelBackward(logical)"
  };
  if (n < 2) return JString(tag[n])+NBTag();
  return tag[n];
}

JString JMouseObj::outputTag(int n) { 
  char* tag[] = { 
    "xpos", 
    "ypos", 
    "lbtn", 
    "mbtn", 
    "rbtn",
    "wheelForward",
    "wheelBackward"
  };
  return JString(tag[n])+NBTag();
}

JFRect JMouseObj::inputArea(int n) { 
  if (n < _LAST-2) 
    return leftArea(n, 0, _LAST-2);
  return topArea(n, _LAST-2, _LAST);
}

JFRect JMouseObj::outputArea(int n) { 
  return rightArea(n, 0, _LAST);
}

int JMouseObj::inputFace(int n) 
{ return (n < _LAST-2) ? LEFT : TOP;}

int JMouseObj::outputFace(int n) 
{ return RIGHT;}

JFPoint JMouseObj::inputPoint(int n, JLinkObj& link) { 
  if (n < _LAST-2) 
    return leftPoint(n, link, 0, _LAST-2);
  return topPoint(n, link, _LAST-2, _LAST);
}

JFPoint JMouseObj::outputPoint(int n, JLinkObj& link) { 
  return rightPoint(n, link, 0, _LAST);
}		     

boolean JMouseObj::gotFocus(JEvent& e) 
{ focusOn = true; return true;}
boolean JMouseObj::lostFocus(JEvent& e) 
{ focusOn = false; return true;}

boolean JMouseObj::globalMouseDown(JEvent& e, int x, int y) {
  if (e.modifiers & JEvent::LBUTTON) {
    state[LBTN] = mask;
    broadcast(LBTN);
  } else if (e.modifiers & JEvent::MBUTTON) {
    state[MBTN] = mask;
    broadcast(MBTN);
  } else if (e.modifiers & JEvent::RBUTTON) {
    state[RBTN] = mask;
    broadcast(RBTN);
  }
  return true;
}

boolean JMouseObj::globalMouseUp(JEvent& e, int x, int y) {
  if (e.modifiers & JEvent::LBUTTON) {
    state[LBTN] = 0;
    broadcast(LBTN);
  } else if (e.modifiers & JEvent::MBUTTON) {
    state[MBTN] = 0;
    broadcast(MBTN);
  } else if (e.modifiers & JEvent::RBUTTON) {
    state[RBTN] = 0;
    broadcast(RBTN);
  }
  return true;
}

boolean JMouseObj::globalMouseMove(JEvent& e, int x, int y) {
  state[XPOS] = x*mask/(JComponent::theRootWindow->width-1);
  state[YPOS] = y*mask/(JComponent::theRootWindow->height-1);
  broadcast(XPOS);
  broadcast(YPOS);
  return true;
}

boolean JMouseObj::globalKeyDown(JEvent& e, int key) {
  switch (key) {
    case JEvent::JK_WheelUp:
      state[WHEEL_FORWARD] = 1;
      broadcast(WHEEL_FORWARD);
      state[WHEEL_FORWARD] = 0;
      broadcast(WHEEL_FORWARD);
      break;			  
    case JEvent::JK_WheelDown:
      state[WHEEL_BACKWARD] = -1;
      broadcast(WHEEL_BACKWARD);
      state[WHEEL_BACKWARD] = 0;
      broadcast(WHEEL_BACKWARD);
      break;
  }
  return true;
}

#if defined(WIN32)
  #include <windows.h>
#endif

void JMouseObj::engine(int n, JLinkObj& link) {
  if (focusOn) return;
#if defined(WIN32)
  POINT pt;
  GetCursorPos(&pt);
  if (n < _LAST-2) {
    switch (n) {
      case XPOS: {
        int newPos;
        link.access(JIntegerData(newPos));
        newPos = max(0, min(mask, newPos));
	SetCursorPos(newPos*
          (JComponent::theRootWindow->width-1)/mask, pt.y);
        break;
      }
      case YPOS: {
        int newPos;
        link.access(JIntegerData(newPos));
        newPos = max(0, min(mask, newPos));
	SetCursorPos(pt.x, newPos*
          (JComponent::theRootWindow->height-1)/mask);
        break;
      }
      case LBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int click;
        link.access(JIntegerData(click));
        if (!click || state[LBTN]) return;
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0L, 0L);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0L, 0L);
        break;
      }
      case MBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int click;
        link.access(JIntegerData(click));
        if (!click || state[MBTN]) return;
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0L, 0L);
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0L, 0L);
        break; 
      }
      case RBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int click;
        link.access(JIntegerData(click));
        if (!click || state[RBTN]) return;
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0L, 0L);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0L, 0L);
	break;
      }
    }
  } else {
    n-=(_LAST-2);
    switch (n) {
      case XPOS: {
        int delta;
        link.access(JIntegerData(delta));
        if (!delta) return;
        SetCursorPos(pt.x+delta, pt.y);
        break;
      }
      case YPOS: {
        int delta;
        link.access(JIntegerData(delta));
        if (!delta) return;
        SetCursorPos(pt.x, pt.y+delta);
        break;
      }
      case LBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int newState;
        link.access(JIntegerData(newState));
        newState = (newState != 0) ? mask : 0;
        if (state[LBTN] == newState) return;
        state[RBTN] = newState;
        mouse_event(
          (newState) ? MOUSEEVENTF_LEFTDOWN : 
          MOUSEEVENTF_LEFTUP, 
          0, 0, 0L, 0L);
        break;
      }
      case MBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int newState;
        link.access(JIntegerData(newState));
        newState = (newState != 0) ? mask : 0;
        if (state[LBTN] == newState) return;
        state[RBTN] = newState;
        mouse_event(
	  (newState) ? MOUSEEVENTF_MIDDLEDOWN : 
	  MOUSEEVENTF_MIDDLEUP, 
	  0, 0, 0L, 0L);
	break;
      }
      case RBTN: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int newState;
        link.access(JIntegerData(newState));
        newState = (newState != 0) ? mask : 0;
        if (state[RBTN] == newState) return;
        state[RBTN] = newState;
        mouse_event(
	  (newState) ? MOUSEEVENTF_RIGHTDOWN : 
	  MOUSEEVENTF_RIGHTUP, 
	  0, 0, 0L, 0L);
	break;
      }
      case WHEEL_FORWARD: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int newState;
        link.access(JIntegerData(newState));
        newState = (newState != 0) ? mask : 0;
        if (state[WHEEL_FORWARD] == newState) return;
        state[WHEEL_FORWARD] = newState;
	if (newState) {
          mouse_event(  
	    MOUSEEVENTF_WHEEL, 
	    0, 0, WHEEL_DELTA, 0L);
	}
	break;
      }
      case WHEEL_BACKWARD: {
        if (JComponent::getJComponent((int)WindowFromPoint(pt))) break;
        int newState;
        link.access(JIntegerData(newState));
        newState = (newState != 0) ? mask : 0;
        if (state[WHEEL_BACKWARD] == newState) return;
        state[WHEEL_BACKWARD] = newState;
	if (newState) {
          mouse_event(
	    MOUSEEVENTF_WHEEL, 
	    0, 0, -WHEEL_DELTA, 0L);
	}
	break;
      }
    }
  }
#endif
}

