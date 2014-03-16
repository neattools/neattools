#include "JEvent.h"
#include "JSystem.h"
#include "JString.h"
#include "JWindow.hpp"

int JEvent::LBUTTON      = 0x0001;
int JEvent::RBUTTON      = 0x0002;
int JEvent::MBUTTON      = 0x0004;
int JEvent::BUTTONS      = 0x0007;
int JEvent::LBUTTON_MASK = 0x0008;
int JEvent::RBUTTON_MASK = 0x0010;
int JEvent::MBUTTON_MASK = 0x0020;
int JEvent::SHIFT_MASK   = 0x0040;
int JEvent::CTRL_MASK    = 0x0080;
int JEvent::CAPS_MASK    = 0x0100;
int JEvent::NUM_MASK     = 0x0200;
int JEvent::SCROLL_MASK  = 0x0400;
int JEvent::META_MASK    = 0x0800;
int JEvent::ALT_MASK     = 0x1000;
int JEvent::DBCLK_MASK   = 0x2000;

char* theJEvent = JEvent().Register();
const char* JEvent::className() const { return "JEvent";}
JObject* JEvent::clone() const { return new JEvent(*this);}

JEvent::JEvent() {
  target = arg = null;
  when = 0;
  id = x = y = key = modifiers = clickCount = 0;
}

JEvent::JEvent(JObject* _target, int _id, JObject* _arg) {
  target = _target;
  id = _id;
  arg = _arg;
  when = JSystem::currentTimeMillis();
  x = y = key = modifiers = clickCount = 0;
}

JEvent::JEvent(JObject* _target, int _id, int _x, int _y,
  int _key, int _modifiers, int _clickCount, JObject* _arg) {
  target = _target;
  when = JSystem::currentTimeMillis();
  id = _id;
  x = _x;
  y = _y;
  key = _key;
  modifiers = _modifiers;
  clickCount = _clickCount;
  arg = _arg;
}

void JEvent::translate(int _x, int _y) {
  x += _x;
  y += _y;
}

boolean JEvent::shiftDown() 
{ return (modifiers & SHIFT_MASK) != 0;}

boolean JEvent::controlDown() 
{ return (modifiers & CTRL_MASK) != 0;}

boolean JEvent::metaDown() 
{ return (modifiers & META_MASK) != 0;}

boolean JEvent::lButtonDown() 
{ return (modifiers & LBUTTON_MASK) != 0;}

boolean JEvent::rButtonDown() 
{ return (modifiers & RBUTTON_MASK) != 0;}

boolean JEvent::mButtonDown() 
{ return (modifiers & MBUTTON_MASK) != 0;}

#if defined(WIN32)

  boolean JEvent::isNumLock() 
  { return (GetKeyState(VK_NUMLOCK) & 1) != 0;}
  boolean JEvent::isScrollLock()
  { return (GetKeyState(VK_SCROLL) & 1) != 0;}
  boolean JEvent::isKeyDown(int keycode)
  { return (GetKeyState(keycode) & 1) != 0;}

  static char *nMap = ")!@#$%^&*(";
  static char *sMap = "~_+{}|:\"<>?";
  static char *vMap = "`-=[]\\;',./";

  int JEvent::VKtoJK(int vKey, long info) {
    int jKey = vKey;
    switch (vKey) {
      case VK_LBUTTON:
      case VK_RBUTTON:
      case VK_MBUTTON:
	jKey = 0;
	break;
      case VK_CANCEL: jKey = JK_Cancel; break;
      case VK_CLEAR: jKey = JK_Clear; break;
      case VK_BACK : jKey = JK_BackSpace; break;
      case VK_TAB :
	if (GetKeyState(VK_SHIFT) < 0)
	  jKey = JK_BackTab;
	else jKey = JK_Tab;
	break;
      case VK_RETURN : jKey = JK_Return; break;
      case VK_SHIFT : {
	jKey = (MapVirtualKey(VK_SHIFT, 0) != (255u & HIWORD(info))) ?
	  JK_ShiftR : JK_Shift; 
	break;
      }
      case VK_CONTROL : 
	jKey = (info & 0x01000000) ?
	  JK_ControlR : JK_Control; 
	break;
      case VK_MENU : 
	jKey = (info & 0x01000000) ?
	  JK_AltR : JK_Alt; 
	break;
      case VK_PAUSE : jKey = JK_Pause; break;
      case VK_CAPITAL : jKey = JK_Caps_Lock; break;
      case VK_ESCAPE : jKey = JK_Escape; break;
      case VK_PRIOR : jKey = JK_Prior; break;
      case VK_NEXT: jKey = JK_Next; break;
      case VK_END : jKey = JK_End; break;
      case VK_HOME : jKey = JK_Home; break;
      case VK_LEFT : jKey = JK_Left; break;
      case VK_UP : jKey = JK_Up; break;
      case VK_RIGHT : jKey = JK_Right; break;
      case VK_DOWN : jKey = JK_Down; break;
      case VK_SELECT : jKey = JK_Select; break;
      case VK_PRINT :
      case VK_SNAPSHOT: jKey = JK_Print; break;
      case VK_EXECUTE : jKey = JK_Execute; break;
      case VK_INSERT : jKey = JK_Insert; break;
      case VK_DELETE : jKey = JK_Delete; break;
      case VK_HELP : jKey = JK_Help; break;
      case VK_MULTIPLY : jKey = JK_KP_Multiply; break;
      case VK_ADD : jKey = JK_KP_Add; break;
      case VK_SEPARATOR : jKey = JK_KP_Separator; break;
      case VK_SUBTRACT : jKey = JK_KP_Subtract; break;
      case VK_DECIMAL : jKey = JK_KP_Decimal; break;
      case VK_DIVIDE : jKey = JK_KP_Divide; break;
      case VK_NUMLOCK : jKey = JK_Num_Lock; break;
      case VK_SCROLL : jKey = JK_Scroll_Lock; break;
      default:
	if (('0'<=vKey) && (vKey<='9')) {
	  if (GetKeyState(VK_SHIFT) < 0) { // '0'-'9'
	    jKey = (int)nMap[vKey-'0'];
	  }
	} else if (('A'<=vKey) && (vKey<='Z')) { // 'A'-'Z'
	  boolean shift = GetKeyState(VK_SHIFT) < 0;
 	  boolean capital = (GetKeyState(VK_CAPITAL) & 1) != 0;
	  if (shift == capital) jKey = vKey+'a'-'A';
	} else if ((VK_NUMPAD0<=vKey) && (vKey<=VK_NUMPAD9)) { // KP_0-KP_9
	  jKey = vKey-VK_NUMPAD0+JK_KP_0;
	} else if ((VK_F1<=vKey) && (vKey<=VK_F24)) { // F1-F16
	  jKey = vKey-VK_F1+JK_F1;
	} else if (vKey > VK_SCROLL) {
	  jKey = MapVirtualKey(vKey, 2);
	  if (GetKeyState(VK_SHIFT) < 0) { // '0'-'9'
	    int index = JString(vMap).indexOf((char)jKey);
	    if (index > -1) jKey = sMap[index];
	  }
	}
    }
    return jKey;
  }

  int JEvent::JKtoVK(int jKey, boolean& needShift) {
    int vKey = jKey;
    needShift = false;
    switch (vKey) {
      case JK_Cancel: vKey = VK_CANCEL; break;
      case JK_Clear: vKey = VK_CLEAR; break;
      case JK_BackSpace: vKey = VK_BACK; break;
      case JK_Tab: vKey = VK_TAB; break;
      case JK_Return: vKey = VK_RETURN; break;
      case JK_Shift: vKey = VK_SHIFT; break;
      case JK_ShiftR: vKey = VK_RSHIFT; break;
      case JK_Control: vKey = VK_CONTROL; break;
      case JK_ControlR: vKey = VK_RCONTROL; break;
      case JK_Alt: vKey = VK_MENU; break;
      case JK_AltR: vKey = VK_RMENU; break;
      case JK_Pause: vKey = VK_PAUSE; break;
      case JK_Caps_Lock: vKey = VK_CAPITAL; break;
      case JK_Escape: vKey = VK_ESCAPE; break;
      case JK_Prior: vKey = VK_PRIOR; break;
      case JK_Next: vKey = VK_NEXT; break;
      case JK_End: vKey = VK_END; break;
      case JK_Home: vKey = VK_HOME; break;
      case JK_Left: vKey = VK_LEFT; break;
      case JK_Up: vKey = VK_UP; break;
      case JK_Right: vKey = VK_RIGHT; break;
      case JK_Down: vKey = VK_DOWN; break;
      case JK_Select: vKey = VK_SELECT; break;
      case JK_Print: vKey = VK_PRINT; break;
      case JK_Execute: vKey = VK_EXECUTE; break;
      case JK_Insert: vKey = VK_INSERT; break;
      case JK_Delete: vKey = VK_DELETE; break;
      case JK_Help: vKey = VK_HELP; break;
      case JK_KP_Multiply: vKey = VK_MULTIPLY; break;
      case JK_KP_Add: vKey = VK_ADD; break;
      case JK_KP_Separator: vKey = VK_SEPARATOR; break;
      case JK_KP_Subtract: vKey = VK_SUBTRACT; break;
      case JK_KP_Decimal: vKey = VK_DECIMAL; break;
      case JK_KP_Divide: vKey = VK_DIVIDE; break;
      case JK_Num_Lock: vKey = VK_NUMLOCK; break;
      case JK_Scroll_Lock: vKey = VK_SCROLL; break;
      default:
        static short kMap[11] = {0};
        if (!kMap[0]) {
          char key;
	  for (short i=128; i<255; i++) {
            key = (char)MapVirtualKey(i, 2);
            for (short j=0; j<11; j++) {
	      if (key == vMap[j]) {
	        kMap[j] = i;
	        break;
              }
	    }
	  }
        }
        int index;
	if (('a'<=jKey) && (jKey<='z')) {
	  vKey = jKey+'A'-'a';
	} else if (('A'<=jKey) && (jKey<='Z')) {
          needShift = true;
	} else if ((JK_KP_0<=jKey) && (jKey<=JK_KP_9)) {
	  vKey = jKey+VK_NUMPAD0-JK_KP_0;
	} else if ((JK_F1<=jKey) && (jKey<=JK_F16)) {
	  vKey = jKey+VK_F1-JK_F1;
	} else if ((index = JString(vMap).indexOf((char)jKey)) > -1) {
          vKey = kMap[index];
	} else if ((index = JString(sMap).indexOf((char)jKey)) > -1) {
          vKey = kMap[index];
          needShift = true;
	} else if ((index = JString(nMap).indexOf((char)jKey)) > -1) {
          vKey = '0'+index;
          needShift = true;
	}
    }
    return vKey;
  }

#else

  boolean NumLockToggle = false;
  boolean ScrollLockToggle = false;

  boolean JEvent::isNumLock() { return NumLockToggle;}
  boolean JEvent::isScrollLock() { return ScrollLockToggle;}

  boolean JEvent::isKeyDown(int keycode) 
  { return (keyMap[keycode >> 3] >> (keycode & 7)) & 1;}

  void JEvent::setKeyState(int keycode, boolean state) { 
    if (state) keyMap[keycode >> 3] |= (1 << (keycode & 7));
    else keyMap[keycode >> 3] &= ~(1 << (keycode & 7));
  }

  int JEvent::VKtoJK(int ks, long info) {
    if ((0xFF95 <= ks) && (ks <=0xFF9B)) 
      return ks-0xFF95+JK_Home;
    switch (ks) {
      case 0xFF9E: return JK_Insert;
      case 0xFF9F: return JK_Delete;
      case JK_Num_Lock:
        NumLockToggle = !NumLockToggle;
        break;
      case JK_Scroll_Lock:
        ScrollLockToggle = !ScrollLockToggle;
        break;
    }
    return ks;
  }

  int JEvent::JKtoVK(int key, boolean& needShift) 
  { needShift = null; return key;}

#endif
