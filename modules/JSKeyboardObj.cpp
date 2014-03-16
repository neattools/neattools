#include "JSKeyboardObj.h"
#include "JLinkObj.h"
#include "JStringData.h"

char* theJSKeyboardObj = JSKeyboardObj().Register();
const char* JSKeyboardObj::className() const { return "JSKeyboardObj";}
JObject* JSKeyboardObj::clone() const { return new JSKeyboardObj(*this);}
JSKeyboardObj::JSKeyboardObj() {
  eventMask = GLOBAL_KEYBOARD_MASK;
  ks[0] = ' ';
  ks[1] = 0;
}

boolean JSKeyboardObj::inputAllowed(int n) { return !inputSet(n).last();}
void JSKeyboardObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("Key"), rect);
}

#if defined(WIN32)
  #include <windows.h>
#endif

extern void vkeyDown(int vKey);
extern void vkeyUp(int vKey);
extern void vkeyStroke(int vKey);
extern void vkeySequence(int jKey);
extern boolean isSequence(int jKey);

void JSKeyboardObj::engine(int n, JLinkObj& link) {
  JString iv;
  link.access(JStringData(iv));
  int sz = iv.length();
#if defined(WIN32)
  boolean needShift;
  for (int i=0; i<sz; i++) {
    uchar jKey = (uchar)iv[i];
    if (isSequence(jKey)) {
      vkeySequence(jKey);
      vkeyUp(VK_MENU);
    } else {
      BYTE vKey = (BYTE)JEvent::JKtoVK(jKey, needShift);
      if (needShift) vkeyDown(VK_SHIFT);
      vkeyStroke(vKey);
      if (needShift) vkeyUp(VK_SHIFT);
    }
  }
#endif
}

boolean JSKeyboardObj::globalKeyDown(JEvent& e, int key) {
  if (key < JEvent::JK_ASCIILast) {
    ks[0] = key;
    value = JString(ks, JString::needCopy);
    broadcast(0);
  }
  return true;
}

boolean JSKeyboardObj::globalKeyUp(JEvent& e, int key) {
  if (key < JEvent::JK_ASCIILast) {
    ks[0] = 0;
    value = JString(ks, JString::needCopy);
    broadcast(0);
  }
  return true;
}

