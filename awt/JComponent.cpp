#include "JComponent.h"
#include "JImage.h"
#include "JString.h"
#include "JDictionary.h"
#include "JAssociation.h"
#include "JBlock.h"
#include "JSystem.h"
#include "JThread.h"
#include "JWindow.hpp"
#include "JLayoutManager.h"
#include "JIllegalArgumentException.h"
#include "JPObject.h"
#include <stdio.h>

#define MAXCLASSNAMESIZE 80
#define MAXTITLESIZE 128

char* theJComponent = JComponent().Register();
int JMouseDrag = null;
int JGlobalMouseDrag = null;
JComponent* JComponent::theMainWindow = null;
JComponent* JComponent::theRootWindow = null;
JArray JComponent::theArgString;

#if !defined(_BASE_LIB)
  DllImport
#endif
extern JDictionary *pClassDict;

#if !defined(_BASE_LIB)
  DllImport
#endif
extern JArray *pClassArray;

  // JohJoh: no idea why I have to do this, but I do (other people had same problem)
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#define WHEEL_DELTA 120 /* Value for rolling one detent */
#endif
 

JHashTable   JComponentContext(101);
JDictionary  JFontTable(37);
long lastClkTime = JSystem::currentTimeMillis();

static char* JFontName[] = {
  "courier",
  "fixed",
  "helvetica",
  "schoolbook",
  "terminal",
  "times"
};

#define JMAXFONT (sizeof(JFontName)/sizeof(char*))

const char* JComponent::className() const { return "JComponent";}
JObject* JComponent::clone() const { return new JComponent(*this);}
boolean JComponent::isWindow() const { return true;}
int JComponent::hashCode() const { return handle & hashMask;}

/* Assume different component classes can be compared */
int JComponent::compareTo(const JObject& s) const 
{ return handle-(*(JComponent*)&s).handle;}

JComponent::JComponent() { 
  handle = 0;
  parent = null;
  foreground = background = null;
  font = null;
  layoutMgr = null;
  resizable = true;
  withCaption = true;
  result = CANCEL;
}

JComponent::JComponent(int _handle, JComponent *_source) { 
  if (!_source) {
    parent = null;
    foreground = background = null;
    font = null;
    layoutMgr = null;
    resizable = true;
    withCaption = true;
    result = CANCEL;
  } else *this = *_source;
  handle = _handle;
}

JComponent::operator int() const { return handle;}
JComponent* JComponent::getParent() { return parent;}
JComponent* JComponent::getTopParent() {
  JComponent *ptr = parent;
  while (ptr->parent != theRootWindow)
    ptr = ptr->parent;
  return ptr;
}


void JComponent::setParent(JComponent& _parent) {
  if (parent && (parent != &_parent))
    _set_parent_(*(parent = &_parent));
}

JArray JComponent::getChildren() { return _get_children_();}
boolean JComponent::hasChild() { return _has_child_();}

void JComponent::add(JComponent& child, int pos) {
  for (JComponent* cn=this; cn; cn=cn->parent) {
    if (cn == &child) 
      throw new JIllegalArgumentException("add parent to itself");
  }
  child.parent->remove(child);
  child.setParent(*this);
}

void JComponent::add(int type, JComponent& child) {
  add(child);
  if (layoutMgr) 
    layoutMgr->addLayoutComponent(type, child);
}

void JComponent::remove(JComponent& child) {
  if ((child.parent == this) && layoutMgr)
    layoutMgr->removeLayoutComponent(child);
}

void JComponent::removeAll() {
  if (layoutMgr) {
    JArray item = getChildren();
    int nmembers = item.size();
    for (int i=0; i<nmembers; i++)
      remove(*(JComponent*)OPTR(item[i]));
  }
}

JLayoutManager JComponent::getLayout() {
  if (layoutMgr) return *layoutMgr;
  return JLayoutManager();
}

void JComponent::setLayout(JLayoutManager& mgr) 
{ SetPObj(layoutMgr, &mgr);}
boolean JComponent::isVisible() { return visible;}

boolean JComponent::isEnabled() { return enabled;}
boolean JComponent::isAncestor(JComponent& ancestor) {
  if (parent) {
    if (parent == &ancestor) return true;
    return parent->isAncestor(ancestor);
  }
  return false;
}

boolean JComponent::isFocusOn()
{ return (_get_focus_() == handle);}

JRect JComponent::bounds() { return *this;}

void JComponent::enable() { 
  if (!enabled) {
    enabled = true;
    _enable_(true);
  }
}

void JComponent::disable() { 
  if (enabled) {
    enabled = false;
    _enable_(false);
  }
}

void JComponent::enable(boolean cond) {
  if (cond) enable();
  else disable();
}

void JComponent::show() {
  if (!visible)	{
    visible = true;
    _show_(visible);
  }
}

void JComponent::hide() {
  if (visible) {
    visible = false;
    _show_(false);
  }
}

void JComponent::show(boolean cond) {
  if (cond) show();
  else hide();
}

void JComponent::setText(JString _text) 
{ _set_text_(text = _text);}

JString JComponent::getText() 
{ return text;}

JColor JComponent::getForeground() {
  if (foreground) return *foreground;
  if (parent) return parent->getForeground();
  return JColor::black;
}

void JComponent::setForeground(JColor c) { 
  SetPObj(foreground, &c);
}

JColor JComponent::getBackground() { 
  if (background) return *background;
  if (parent) return parent->getBackground();
  return JColor::lightGray;
}

void JComponent::setBackground(JColor c) { 
  SetPObj(background, &c);
}

JFont JComponent::getJFont() { 
  if (font) return *font;
  if (parent) return parent->getJFont();
  return JFont::standard;
}

void JComponent::setJFont(JFont f) {
  SetPObj(font, &f);
}

void JComponent::move(int _x, int _y)
{ reshape(_x, _y, width, height);}

JRect& JComponent::reshape(int _x, int _y, int _width, int _height) {
  if (this == JComponent::theMainWindow) {
    if (getMaximized()) {
      setRestored();
      _x = x;
      _y = y;
    }
  }
  _reshape_(_x, _y, _width, _height);
  return *this;
}

JRect& JComponent::reshape(JRect rect)
{ return reshape(rect.x, rect.y, rect.width, rect.height);}

JInsets JComponent::insets() { return JInsets();}
JDimension JComponent::preferredSize() {
  if (layoutMgr) return layoutMgr->preferredLayoutSize(*this);
  return size();
}

JDimension JComponent::minimumSize() {
  if (layoutMgr) return layoutMgr->minimumLayoutSize(*this);
  return size();
}

void JComponent::startup() {}

void JComponent::layout() {
  if (hasChild() && layoutMgr)
    layoutMgr->layout(*this);
  if (needRedraw()) repaint();
}

void JComponent::layoutMinimized() {}
void JComponent::layoutMaximized() {}
void JComponent::layoutRestored() {}

void JComponent::destroy() {
  DelPObj(font);
  DelPObj(foreground);
  DelPObj(background);
  DelPObj(layoutMgr);
  if (parent && parent->layoutMgr)
    parent->layoutMgr->removeLayoutComponent(*this);
}

void JComponent::dispose() { _destroy_();}
void JComponent::kill() { _kill_();}
void JComponent::activate() {}
void JComponent::deactivate() {}
void JComponent::idleAction(int id) {}
void JComponent::toFront() { _raise_window_();}
void JComponent::toBack() { _bottom_window_();}
void JComponent::toTopMost() { _top_most_window_();}
void JComponent::toNonTopMost() { _non_top_most_window_();}

JGraphics JComponent::getJGraphics() 
{ return JGraphics(_get_dc_(), *this);}

void JComponent::beforePaint(JRect *rect) {}
void JComponent::afterPaint(JRect *rect) {}
void JComponent::paint(JGraphics g) {
  g.setJColor(getBackground());
  g.fillJRect(g.getClipJRect());
}

void JComponent::repaint(boolean update) 
{ repaint(0, 0, width, height, update);}

void JComponent::repaint(JRect r, boolean update) 
{ repaint(r.x, r.y, r.width, r.height, update);}

void JComponent::repaint(JRegion rgn, boolean update) 
{ _repaint_(rgn, update);}

void JComponent::repaint(int x, int y, int width, int height, boolean update) 
{ _repaint_(x, y, width, height, update);}

void JComponent::updateInvalidArea() 
{ _update_invalid_area_();}

void JComponent::ScrollWindow(int x, int y, int width, int height, int dx, int dy) {
  if (!dx && !dy) return;
  JGraphics g = getJGraphics();
  repaint(g.scrollArea(x, y, width, height, dx, dy), true);
}

JComponent* JComponent::locate(int x, int y) 
{ return inside(x, y) ? this : null;}

void JComponent::setMousePos(int x, int y)
{ _set_mouse_pos_(x, y);}

void JComponent::translateJEvent(JEvent& e, JComponent* dest) {
  JComponent *target = dest;
  do {
    e.translate(-target->x, -target->y);
    target = target->parent;
  } while (target != this);
}

void JComponent::reverseJEvent(JEvent& e, JComponent* dest) {
  JComponent *target = this;
  do {
    e.translate(target->x, target->y);
    target = target->parent;
  } while (target != dest);
}

boolean JComponent::postJEvent(JEvent& e) {
  if (handleJEvent(e)) return true;
  if (parent && (parent != theRootWindow)) {
    e.translate(x, y);
    if (parent->postJEvent(e)) return true;
  }
  return false;
}

boolean JComponent::handleJEvent(JEvent& e) {
  switch (e.id) {
    case JEvent::MOUSE_ENTER:
      return mouseEnter(e, e.x, e.y);
    case JEvent::MOUSE_EXIT:
      return mouseExit(e, e.x, e.y);
    case JEvent::MOUSE_MOVE:
      return mouseMove(e, e.x, e.y);
    case JEvent::MOUSE_DOWN:
    case JEvent::MOUSE_ACTION:
      return mouseDown(e, e.x, e.y);
    case JEvent::MOUSE_DRAG:
      return mouseDrag(e, e.x, e.y);
    case JEvent::MOUSE_UP:
      return mouseUp(e, e.x, e.y);
    case JEvent::KEY_PRESS:
    case JEvent::KEY_ACTION:
      return keyDown(e, e.key);
    case JEvent::KEY_RELEASE:
      return keyUp(e, e.key);
    case JEvent::ACTION_EVENT:
      return action(e, e.arg);
    case JEvent::GOT_FOCUS:
      return gotFocus(e, e.arg);
    case JEvent::LOST_FOCUS:
      return lostFocus(e, e.arg);
    case JEvent::CHILD_NOTIFY: // Notify from Child
      return childNotify(e, e.arg);
    case JEvent::PARENT_NOTIFY: // Notify from Parent
      return parentNotify(e, e.arg);
    case JEvent::PEER_NOTIFY: // Notify from Peer
      return peerNotify(e, e.arg);
    case JEvent::DATA_NOTIFY: // DataNotify
      return dataNotify(e, e.arg);
    case JEvent::AUX_NOTIFY: // AuxNotify
      return auxNotify(e, e.arg);
    case JEvent::WINDOW_CLOSE_QUERY: // Close Query
      return closeQuery(e);
  }
  return false;
}

boolean JComponent::mouseEnter(JEvent& e, int x, int y) { return false;}
boolean JComponent::mouseExit(JEvent& e, int x, int y) { return false;}
boolean JComponent::mouseMove(JEvent& e, int x, int y) { return false;}
boolean JComponent::mouseDown(JEvent& e, int x, int y) { return false;}
boolean JComponent::mouseDrag(JEvent& e, int x, int y) { return false;}
boolean JComponent::mouseUp(JEvent& e, int x, int y) { return false;}
boolean JComponent::keyDown(JEvent& e, int key)	{ return false;}
boolean JComponent::keyUp(JEvent& e, int key) { return false;}
boolean JComponent::action(JEvent& e, JObject* arg) { return false;}
boolean JComponent::gotFocus(JEvent& e, JObject* arg) { return false;}
boolean JComponent::lostFocus(JEvent& e, JObject* arg) { return false;}
boolean JComponent::childNotify(JEvent& e, JObject* arg) { return false;}
boolean JComponent::parentNotify(JEvent& e, JObject* arg) { return false;}
boolean JComponent::peerNotify(JEvent& e, JObject* arg) { return false;}
boolean JComponent::dataNotify(JEvent& e, JObject* arg) { return false;}
boolean JComponent::auxNotify(JEvent& e, JObject* arg) { return false;}
boolean JComponent::closeQuery(JEvent& e) { return true;}
boolean JComponent::useImage() { return false;}
boolean JComponent::needRedraw() { return false;}
void JComponent::requestFocus() { _set_focus_();}
void nextFocus() {}

int JComponent::maxFontList() 
{ return JMAXFONT;}

char** JComponent::getFontList() 
{ return JFontName;}
  
JComponent* JComponent::getJComponent(int handle) 
{ return (JComponent*)JComponentContext[JComponent(handle)];}

#if defined(WIN32)

  #include "JDList.h"
  #include "JInteger.h"
  #include "JInetAddress.h"
  #include "JFile.h"
  #include "JFile.hpp"

  #define MAXCLASSNAME	256
  #define ID_ASSIGN	0x102
  #define ID_SETUP	0x103
  #define ID_SETCOUNT	0x104
  #define ID_INSERT	0x105
  #define ID_DELETE	0x106

  char* JFontInternal[] = {  
    "Courier New",
    "Fixedsys",
    "Arial",
    "Bookman Old Style",
    "Terminal",
    "Times New Roman"
  };

  #include "JCriticalSection.h"
  JCriticalSection mouseButton;
  JCriticalSection detach;
  HINSTANCE JMicroSoft::hInstance;
  HINSTANCE JMicroSoft::hPrevInstance;
  LPSTR JMicroSoft::lpszCmdLine;
  int JMicroSoft::nCmdShow;
  int JMicroSoft::theContextCount = 0;
  JHashTable JMicroSoft::JObjectCache(101);

  void JComponent::setMinimized() { ShowWindow((HWND)handle, SW_MINIMIZE);}
  boolean JComponent::getMinimized() { return (IsIconic((HWND)handle) != 0);}
  void JComponent::setMaximized() { 
    ShowWindow((HWND)handle, SW_MAXIMIZE);
  }
  boolean JComponent::getMaximized() { return (IsZoomed((HWND)handle) != 0);}
  void JComponent::setRestored() { 
    ShowWindow((HWND)handle, SW_RESTORE);
  }
  boolean JComponent::getRestored() { return !getMinimized() && !getMaximized();}

  void JComponent::setup(int _handle, int _parent) {
    handle = _handle;
    parent = getJComponent(_parent);
    enabled = _is_enabled_();
    visible = _is_visible_();
  }

  #define RESIZABLE (WS_MAXIMIZEBOX|WS_THICKFRAME)
  #define CAPTION (WS_CAPTION)

  void JComponent::setResizable(boolean _resizable) {
    if (resizable == _resizable) return;
	int ox = x;
	int oy = y;
	int owidth = width;
	int oheight = height;
    resizable = _resizable;
    long style = GetWindowLong((HWND)handle, GWL_STYLE);
    if (resizable) style |= RESIZABLE;
    else style &= ~RESIZABLE;
    SetWindowLong((HWND)handle, GWL_STYLE, style);
    _reshape_(ox, oy, owidth, oheight);
  }

  void JComponent::setCaption(boolean _withCaption) {
    if (withCaption == _withCaption) return;
	int ox = x;
	int oy = y;
	int owidth = width;
	int oheight = height;
    withCaption = _withCaption;
    long style = GetWindowLong((HWND)handle, GWL_STYLE);
    if (withCaption) style |= CAPTION;
    else style &= ~CAPTION;
    SetWindowLong((HWND)handle, GWL_STYLE, style);
    if (getMaximized()) {
      int cy = GetSystemMetrics(SM_CYCAPTION);
      if (withCaption) cy = -cy;
      _reshape_(ox, oy-cy, owidth, oheight+cy);
    } else _reshape_(ox, oy, owidth, oheight);
  }

  int JEventModifier(int button) {
    int result = button;
    if (GetKeyState(VK_CONTROL) < 0) result |= JEvent::CTRL_MASK;
    if (GetKeyState(VK_SHIFT) < 0) result |= JEvent::SHIFT_MASK;
    if (GetKeyState(VK_MENU) < 0) result |= JEvent::ALT_MASK;
    if (GetKeyState(VK_CAPITAL) & 1) result |= JEvent::CAPS_MASK;
    if (GetKeyState(VK_NUMLOCK) & 1) result |= JEvent::NUM_MASK;
    if (GetKeyState(VK_SCROLL) & 1) result |= JEvent::SCROLL_MASK;
    return result;
  }

  HWND hLastCaptured = null;
  HWND hList = null;
  int nButtonPressed = 0;

  int isMainWindowTopMost() {
    if (!JComponent::theMainWindow) return 0;
    LONG style = GetWindowLong(
      (HWND)(int)*JComponent::theMainWindow, GWL_EXSTYLE);
    return (style & WS_EX_TOPMOST) != 0;
  }

  long CALLBACK StdWndProc(HWND hWnd, UINT iMessage,
    WPARAM wParam, LPARAM lParam) {
    static POINT cp, gp;
    JComponent *theJComponent = JComponent::getJComponent((int)hWnd);
    if (!theJComponent) {
      char cName[MAXCLASSNAMESIZE];
      if (GetClassName(hWnd, cName, MAXCLASSNAMESIZE)) {
        theJComponent = (JComponent*)(*pClassDict)[JString(cName).toUpperCase()];
        if (theJComponent) {
	  theJComponent = (JComponent*)theJComponent->clone();
          theJComponent->setup((int)hWnd, (int)GetParent(hWnd));
          JComponentContext.add(*theJComponent);
          delete theJComponent;
          theJComponent = JComponent::getJComponent((int)hWnd);
	}
      }
    }
    if (theJComponent) {
      JComponent &c = *theJComponent;
      switch (iMessage) {
        case WM_WINDOWPOSCHANGING: {
          LPWINDOWPOS lpwp = (LPWINDOWPOS)lParam;
          if (&c != JComponent::theMainWindow) break;
          if ((lpwp->hwndInsertAfter != HWND_TOP) ||
            (lpwp->flags & SWP_NOZORDER)) break;
          HWND next = GetWindow(hWnd, GW_HWNDFIRST);
          do { next = GetWindow(next, GW_HWNDNEXT);
          } while (GetWindowLong(next, GWL_EXSTYLE) & WS_EX_TOPMOST);
          next = GetWindow(next, GW_HWNDPREV);
          if (next && next != hWnd) {
            lpwp->hwndInsertAfter = next;
          } else lpwp->flags |= SWP_NOZORDER;
          return 0L;
        }
        case WM_MOUSEACTIVATE:
          if (HTCAPTION == LOWORD(lParam)) break;
          if (&c != JComponent::theMainWindow) break;
          if (isMainWindowTopMost() && !GetFocus()) {
            HWND next = hWnd;
            do { next = GetWindow(next, GW_HWNDNEXT);
            } while (!IsWindowVisible(next) ||
              (GetWindowLong(next, GWL_EXSTYLE) & WS_EX_TOPMOST));
            if (next) {
               SetForegroundWindow(next);
               BringWindowToTop(next);
            }
            return MA_NOACTIVATE;
          }
          break;
	case WM_ACTIVATEAPP:
          if (JComponent::theMainWindow)
            if (isMainWindowTopMost()) return 0L;
	  if (wParam) JComponent::theMainWindow->activate();
	  else JComponent::theMainWindow->deactivate();
	  return 0L;
        case WM_CREATE: {
	  JMicroSoft::theContextCount++;
          theJComponent->arg = (void**)
	    ((LPCREATESTRUCT)lParam)->lpCreateParams;
	  theJComponent->startup();
	  return 0L;
	}
        case WM_GETMINMAXINFO : {
          MINMAXINFO *lpmmi = (LPMINMAXINFO)lParam;
          lpmmi->ptMinTrackSize.x = 0;
          return 0L;
        }
        case WM_MOVE: {
	  if (IsIconic(hWnd)) break;
	  POINT pt = { 0, 0};
	  ClientToScreen(hWnd, &pt);
	  ScreenToClient(GetParent(hWnd), &pt);
	  c.x = pt.x;
	  c.y = pt.y;
	  return 0L;
        }
        case WM_SIZE: {
	  switch (wParam) {
	    case SIZE_MINIMIZED:
	      c.layoutMinimized();
	      return 0L;
	    case SIZE_MAXIMIZED:
	      c.layoutRestored();
	      c.layoutMaximized();
	      break;
	    case SIZE_RESTORED:
	      c.layoutRestored();
	      break;
	    default:
	      return 0L;
	  }
          int nw = LOWORD(lParam);
          int nh = HIWORD(lParam);
	  if ((nw != c.width) || (nh != c.height)) {
            c.width = nw;
            c.height = nh;
            c.layout();
	  }
	  return 0L;
        }
	case WM_PAINT: {
	  static int counter = 0;
	  if (counter++ > 0) MessageBeep(0xFFFF);
	  PAINTSTRUCT ps;
	  BeginPaint(hWnd, &ps);
          JGraphics g((int)ps.hdc, c, false);
          JRect rect = g.getClipJRect();
	  c.beforePaint(&rect);
          if (c.useImage()) {
	    JImage image(rect.width, rect.height);
	    JGraphics bg = image.getJGraphics(c);
	    bg.translate(rect.x, rect.y);
	    bg.setClipJRect(rect);
	    c.paint(bg);
	    bg.Release();
	    g.drawJImage(image, rect.x, rect.y);
	  } else c.paint(g);
	  EndPaint(hWnd, &ps);
	  c.afterPaint(&rect);
	  counter--;
	  return 0L;
	}
	case WM_CLOSE : {
          JEvent event(&c,
	    JEvent::WINDOW_CLOSE_QUERY);
	  if (c.postJEvent(event)) break;
	  return 0L;
	}
	case WM_DESTROY: {
	  c.destroy();
	  return 0L;
	}
	case WM_NCDESTROY: {
	  JComponentContext.del(JComponent((int)hWnd));
	  if (!--JMicroSoft::theContextCount)
            PostQuitMessage(0);
	  return 0L;
	}
        case WM_SYSCOMMAND:
	  if ((wParam == SC_KEYMENU) && !lParam) return 0L;
	  break;
	case WM_TIMER: {
	  boolean needAction = false;
	  switch (wParam) {
	    case WM_LBUTTONDOWN:
	      KillTimer(hWnd, wParam);
	      JMouseDrag &= ~JEvent::BUTTONS;
	      JMouseDrag |= JEvent::LBUTTON;
	      needAction = (JMouseDrag & JEvent::LBUTTON_MASK) != 0;
	      break;
	    case WM_MBUTTONDOWN: 
	      KillTimer(hWnd, wParam);
	      JMouseDrag &= ~JEvent::BUTTONS;
	      JMouseDrag |= JEvent::MBUTTON;
	      needAction = (JMouseDrag & JEvent::MBUTTON_MASK) != 0;
	      break;
	    case WM_RBUTTONDOWN: 
	      KillTimer(hWnd, wParam);
	      JMouseDrag &= ~JEvent::BUTTONS;
	      JMouseDrag |= JEvent::RBUTTON;
	      needAction = (JMouseDrag & JEvent::RBUTTON_MASK) != 0;
	      break;
	  }
	  if (needAction) {
            JEvent event(&c,
	      JEvent::MOUSE_ACTION, 
	      cp.x, cp.y, 0,
              JEventModifier(JMouseDrag));
	    c.postJEvent(event);
	    SetTimer(hWnd, wParam, 100, null);
	  }
	  break;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN: 
	case WM_MBUTTONDOWN: {
	  if (!nButtonPressed++) SetCapture(hWnd);
          else if (GetCapture() != hWnd) {
            nButtonPressed = 1;
            SetCapture(hWnd);
          }
          JMouseDrag &= ~JEvent::BUTTONS;
          switch (iMessage) {
	    case WM_LBUTTONDOWN:
	      JMouseDrag |= JEvent::LBUTTON;
	      JMouseDrag |= JEvent::LBUTTON_MASK;
	      break;
	    case WM_MBUTTONDOWN:
	      JMouseDrag |= JEvent::MBUTTON;
	      JMouseDrag |= JEvent::MBUTTON_MASK;
	      break;
	    case WM_RBUTTONDOWN:
	      JMouseDrag |= JEvent::RBUTTON;
	      JMouseDrag |= JEvent::RBUTTON_MASK;
	      break;
	  }
          JEvent event(&c,
	    JEvent::MOUSE_DOWN, 
	    cp.x = (short)LOWORD(lParam),
	    cp.y = (short)HIWORD(lParam), 
	    0,JEventModifier(JMouseDrag));
          if ((event.when > lastClkTime) && 
            (event.when-lastClkTime < 300))
	    event.modifiers |= JEvent::DBCLK_MASK;
          lastClkTime = event.when;
	  c.postJEvent(event);
	  SetTimer(hWnd, iMessage, 400, null);
	  return 0L;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: 
	case WM_MBUTTONUP: {
          if (!nButtonPressed) break;
	  if (!--nButtonPressed) ReleaseCapture();
          JMouseDrag &= ~JEvent::BUTTONS;
	  switch (iMessage) {
	    case WM_LBUTTONUP: 
	      JMouseDrag |= JEvent::LBUTTON;
	      JMouseDrag &= ~JEvent::LBUTTON_MASK;
	      KillTimer(hWnd, WM_LBUTTONDOWN);
	      break;
	    case WM_MBUTTONUP: 
	      JMouseDrag |= JEvent::MBUTTON;
	      JMouseDrag &= ~JEvent::MBUTTON_MASK;
	      KillTimer(hWnd, WM_MBUTTONDOWN);
	      break;
	    case WM_RBUTTONUP: 
	      JMouseDrag |= JEvent::RBUTTON;
	      JMouseDrag &= ~JEvent::RBUTTON_MASK;
	      KillTimer(hWnd, WM_RBUTTONDOWN);
	      break;
	  }
          JEvent event(&c,
	    JEvent::MOUSE_UP,
	    cp.x = (short)LOWORD(lParam),
	    cp.y = (short)HIWORD(lParam),
	    0, JEventModifier(JMouseDrag));
	  c.postJEvent(event);
	  return 0L;
        }
	case WM_MOUSEMOVE: {
	  JMouseDrag &= ~JEvent::BUTTONS;
	  cp.x = (short)LOWORD(lParam);
	  cp.y = (short)HIWORD(lParam);
          JEvent event(&c,
	    (JMouseDrag ? JEvent::MOUSE_DRAG : JEvent::MOUSE_MOVE),
	    cp.x, cp.y, 0,
	    JEventModifier(JMouseDrag));
	  c.postJEvent(event);
	  return 0L;
	}
	case WM_MOUSEWHEEL: {
	  int key = ((int)(short)LOWORD(lParam) == WHEEL_DELTA) ? 
	    JEvent::JK_WheelUp : JEvent::JK_WheelDown;
          JEvent event(&c,
	    (JEvent::KEY_ACTION),
	    cp.x, cp.y, key,
	    JEventModifier(JMouseDrag));
	  c.postJEvent(event);
	  return 0L;
	}
	case WM_SYSCHAR:
	case WM_CHAR: {
          int jKey = wParam;
          if (jKey > 126) {
            JEvent event(&c, JEvent::KEY_ACTION, cp.x, cp.y, jKey,
              JEventModifier(JMouseDrag), 
	      LOWORD(lParam));
	    c.postJEvent(event);
          }
          break;
        }
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYDOWN:
	case WM_KEYUP: {
          MSG msg = { hWnd, iMessage, wParam, lParam};
	  int id;
	  int jKey = JEvent::VKtoJK(wParam, lParam);
	  if (lParam >= 0) {
	    id = ((lParam & 0x40000000) ?
	      JEvent::KEY_ACTION :
	      JEvent::KEY_PRESS);
	  } else id = JEvent::KEY_RELEASE;
          JEvent event(&c,
            id,	cp.x, cp.y, jKey,
	    JEventModifier(JMouseDrag), 
	    LOWORD(lParam));
	  c.postJEvent(event);
          TranslateMessage(&msg);
	  break;
	}
        case WM_COPYDATA: {
          PCOPYDATASTRUCT pcds = (PCOPYDATASTRUCT)lParam;
          PFILTERDATA pfmd = (PFILTERDATA)pcds->lpData;
	  UINT im = pcds->dwData;
          WPARAM wp = pfmd->wParam;
	  if (im == UM_KEYBOARD)
	    PostMessage(hWnd, im, wp, pfmd->lParam);
	  else StdWndProc(hWnd, im, wp, (LPARAM)pfmd->extraData);
          return 1L;
        }
	case UM_KEYBOARD: {
	  if (!JComponent::theMainWindow) return 0L;
	  detach.lock();
	  int id;
	  int jKey = JEvent::VKtoJK(wParam, lParam);
	  if (lParam >= 0) {
	    id = ((lParam & 0x40000000) ?
	      JEvent::GLOBAL_KEY_ACTION :
	      JEvent::GLOBAL_KEY_PRESS);
            JEvent event(JComponent::theMainWindow,
              id, gp.x, gp.y, jKey,
	      JEventModifier(JGlobalMouseDrag), 
	      LOWORD(lParam));
	    JComponent::theMainWindow->postJEvent(event);
	  } else {
	    id = JEvent::GLOBAL_KEY_RELEASE;
            JEvent event(JComponent::theMainWindow,
              id, gp.x, gp.y, jKey,
	      JEventModifier(JGlobalMouseDrag), 
	      LOWORD(lParam));
	    JComponent::theMainWindow->postJEvent(event);
	  }
	  detach.unlock();
	  return 0L;
	}
	case UM_MOUSE: {
	  static boolean inside = false;
	  if (!JComponent::theMainWindow) return 0L;
	  detach.lock();
          UINT type = wParam;
          LPMOUSEHOOKSTRUCT lpMHS = (LPMOUSEHOOKSTRUCT)lParam;
	  HWND current = lpMHS->hwnd;
	  POINT &pt = lpMHS->pt;
          if (type == WM_NCMOUSEMOVE) {
            type = WM_MOUSEMOVE;
          }
	  if (type != WM_MOUSEMOVE) {
	    JGlobalMouseDrag &= ~JEvent::BUTTONS;
	    switch (type) {
	      case WM_MOUSEWHEEL: 
	    	break;
	      case WM_NCLBUTTONDOWN:
	      case WM_NCMBUTTONDOWN:
	      case WM_NCRBUTTONDOWN:
	      case WM_NCLBUTTONDBLCLK:
	      case WM_NCMBUTTONDBLCLK:
	      case WM_NCRBUTTONDBLCLK:
	      case WM_LBUTTONDOWN:
	      case WM_MBUTTONDOWN:
	      case WM_RBUTTONDOWN:
	      case WM_LBUTTONDBLCLK:
	      case WM_MBUTTONDBLCLK:
	      case WM_RBUTTONDBLCLK: {
		switch (type) {
	          case WM_LBUTTONDOWN:
	          case WM_LBUTTONDBLCLK:
	          case WM_NCLBUTTONDOWN:
	          case WM_NCLBUTTONDBLCLK:
	            JGlobalMouseDrag |= JEvent::LBUTTON;
	            JGlobalMouseDrag |= JEvent::LBUTTON_MASK;
		    break;
	          case WM_MBUTTONDOWN:
	          case WM_MBUTTONDBLCLK:
	          case WM_NCMBUTTONDOWN:
	          case WM_NCMBUTTONDBLCLK:
	            JGlobalMouseDrag |= JEvent::MBUTTON;
	            JGlobalMouseDrag |= JEvent::MBUTTON_MASK;
	            break;
	          case WM_RBUTTONDOWN:
		  case WM_RBUTTONDBLCLK:
	          case WM_NCRBUTTONDOWN:
	          case WM_NCRBUTTONDBLCLK:
	            JGlobalMouseDrag |= JEvent::RBUTTON;
	            JGlobalMouseDrag |= JEvent::RBUTTON_MASK;
		    break;
		}
                JEvent event(JComponent::theMainWindow,
	          JEvent::GLOBAL_MOUSE_DOWN, 
	          pt.x, pt.y, 0, 
		  JEventModifier(JGlobalMouseDrag));
		JComponent::theMainWindow->postJEvent(event);
		break;
	      }
	      case WM_NCLBUTTONUP: 
	      case WM_NCMBUTTONUP: 
	      case WM_NCRBUTTONUP:
	      case WM_LBUTTONUP: 
	      case WM_MBUTTONUP: 
	      case WM_RBUTTONUP: {
		switch (type) {
	          case WM_LBUTTONUP: 
	          case WM_NCLBUTTONUP: 
	            JGlobalMouseDrag |= JEvent::LBUTTON;
	            JGlobalMouseDrag &= ~JEvent::LBUTTON_MASK;
	            break;
	          case WM_MBUTTONUP: 
	          case WM_NCMBUTTONUP: 
	            JGlobalMouseDrag |= JEvent::MBUTTON;
	            JGlobalMouseDrag &= ~JEvent::MBUTTON_MASK;
	            break;
	          case WM_RBUTTONUP: 
	          case WM_NCRBUTTONUP: 
	            JGlobalMouseDrag |= JEvent::RBUTTON;
	            JGlobalMouseDrag &= ~JEvent::RBUTTON_MASK;
	            break;
		}
                JEvent event(JComponent::theMainWindow,
	          JEvent::GLOBAL_MOUSE_UP, 
	          pt.x, pt.y, 0, 
		  JEventModifier(JGlobalMouseDrag));
		JComponent::theMainWindow->postJEvent(event);
	      }
	    }
	    gp = pt;
	    detach.unlock();
	    return 0L;
	  }
	  HWND hNextCaptured = current;
          JEvent event(JComponent::theMainWindow,
	    JEvent::GLOBAL_MOUSE_MOVE,
	    pt.x, pt.y, 0,
	    JEventModifier(JGlobalMouseDrag));
          JComponent::theMainWindow->postJEvent(event);
          JComponent *nc = JComponent::getJComponent((int)hNextCaptured);
          if (nc) {
            if (hNextCaptured != hLastCaptured) {
	      JComponent *jc = JComponent::getJComponent((int)hLastCaptured);
	      if (jc && hLastCaptured) {
	        POINT np = pt;
	        ScreenToClient(hLastCaptured, &np);
                JEvent event(jc,
	          JEvent::MOUSE_EXIT,
	          np.x, np.y, 0,
	          JEventModifier(JGlobalMouseDrag));
	        jc->postJEvent(event);
              }
	      POINT np = pt;
	      inside = true;
	      ScreenToClient(hNextCaptured, &np);
              JEvent event(nc,
	        JEvent::MOUSE_ENTER, 
	        np.x, np.y, 0,
	        JEventModifier(JGlobalMouseDrag));
	      nc->postJEvent(event);
              hLastCaptured = hNextCaptured;
            } else {
	      JRect client(0, 0, nc->width, nc->height);
	      ScreenToClient(hNextCaptured, &pt);
	      if (inside != client.inside(pt.x, pt.y)) {
		inside = !inside;
                JEvent event(nc,
		  ((inside) ? JEvent::MOUSE_ENTER : JEvent::MOUSE_EXIT), 
	          pt.x, pt.y, 0,
	          JEventModifier(JGlobalMouseDrag));
	        nc->postJEvent(event);
              }
            }
	  }
	  detach.unlock();
	  return 0L;
	}
	case UM_GETMESSAGE: {
	  if (!JComponent::theMainWindow) return 0L;
          LPMSG lpMSG = (LPMSG)lParam;
          switch (lpMSG->message) {
	    case WM_MOUSEWHEEL: 
	    {
	      POINT pt;
	      GetCursorPos(&pt);
  	      int key = ((int)(short)HIWORD(lpMSG->wParam) == WHEEL_DELTA) ? 
		JEvent::JK_WheelUp : JEvent::JK_WheelDown;
              JEvent event(JComponent::theMainWindow,
	        JEvent::GLOBAL_KEY_ACTION, 
	        pt.x, pt.y, key, 
		JEventModifier(JGlobalMouseDrag));
	      JComponent::theMainWindow->postJEvent(event);
	      break;
	    }
	  }
	  return 0L;
	}
	case UM_DATA: {
          JEvent event(&c, JEvent::DATA_NOTIFY, 
	    0, 0, wParam, lParam);
          c.postJEvent(event);
	  return 0L;
	}
	case UM_AUX: {
          JEvent event(&c, JEvent::AUX_NOTIFY, 
	    0, 0, wParam, lParam);
          c.postJEvent(event);
	  return 0L;
	}
	case UM_DEBUG: {
          if (!hList) {
            hList = CreateWindow("listbox", "debug",
	      WS_CAPTION | WS_SIZEBOX | 
	      WS_POPUP | WS_VISIBLE | 
	      WS_VSCROLL,
	      10, 10, 400, 400, null, 
	      null, JMicroSoft::hInstance, 
	      null);
            ShowWindow(hList, SW_NORMAL);
            UpdateWindow(hList);
          }
          SendMessage(hList, LB_ADDSTRING, 0, lParam);
          SendMessage(hList, LB_SETCARETINDEX, wParam-1, 0L);
          return 0L;
	}
	case UM_IDLE: {
          c.idleAction(wParam);
	  return 0L;
	}
	case WM_SETFOCUS: {
          JEvent event(&c, JEvent::GOT_FOCUS);
	  event.arg = JComponent::getJComponent((int)wParam);
          c.postJEvent(event);
	  return 0L;
	}
	case WM_KILLFOCUS: {
          JEvent event(&c, JEvent::LOST_FOCUS);
	  event.arg = JComponent::getJComponent((int)wParam);
          c.postJEvent(event);
	  return 0L;
	}
	case MM_MIXM_LINE_CHANGE : {
          JEvent event(&c, JEvent::MIXER_LINE_NOTIFY,
	    0, 0, wParam, lParam);
	  c.postJEvent(event);
	  return 0L;
	}
	case MM_MIXM_CONTROL_CHANGE : {
          JEvent event(&c, JEvent::MIXER_CONTROL_NOTIFY,
	    0, 0, wParam, lParam);
	  c.postJEvent(event);
	  return 0L;
	}
      }
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
  }

  int JComponent::loadDynLinkLibrary(JString name) {
    int result = (int)LoadLibrary(name);
    if (!result) {
      JFile file(name);
      result = (int)LoadLibrary(file.getPath());
    }
    return result;
  }

  void JComponent::freeDynLinkLibrary(int handle) 
  { FreeLibrary((HMODULE)handle);}

  JComponent* JComponent::createJComponent(char* name, 
    JComponent* p, void** arg) {
    HWND hWnd = CreateWindow(name, "", 
      WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
      0, 0, 0, 0, (HWND)(int)*p, 
      null, (HINSTANCE)JMicroSoft::hInstance, (LPVOID)arg);
    if (!hWnd) return null;
    return (hWnd) ? getJComponent((int)hWnd) : null;
  }
  
  JComponent* JComponent::createJWindow(char* name, 
    JComponent* p, void** arg) {
    HWND hWnd = CreateWindow(name, "", 
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      0, 0, 0, 0, (HWND)(int)*p, 
      null, JMicroSoft::hInstance, arg);
    return (hWnd) ? getJComponent((int)hWnd) : null;
  }

  JComponent* JComponent::createJDialog(char* name, 
    JComponent* p, boolean widthSysMenu, void** arg) {
    HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, name, "", 
      WS_POPUP | WS_CLIPCHILDREN | WS_CAPTION | WS_DLGFRAME
      | WS_SIZEBOX | ((widthSysMenu) ? WS_SYSMENU : 0),
      0, 0, 0, 0, (HWND)(int)*p, 
      null, JMicroSoft::hInstance, (LPVOID)arg);
    return (hWnd) ? getJComponent((int)hWnd) : null;
  }
  
  JComponent* JComponent::createJModal(char* name, 
    JComponent* p, void** arg) {
    HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, name, "", 
      WS_POPUP | WS_CLIPCHILDREN | WS_CAPTION | WS_DLGFRAME
      | WS_SYSMENU, 0, 0, 0, 0, (HWND)(int)*p, 
      null, JMicroSoft::hInstance, (LPVOID)arg);
    return (hWnd) ? getJComponent((int)hWnd) : null;
  }
  
  void DoRegister(const JObject* obj, void** arg) {
    JComponent *theJComponent = (JComponent*)(*(JAssociation*)obj).value();
    if (!theJComponent) return;
    if (!theJComponent->isWindow()) return;
    WNDCLASS AWndClass;
    AWndClass.cbClsExtra = 0;
    AWndClass.cbWndExtra = 0;
    AWndClass.hInstance = JMicroSoft::hInstance;
    AWndClass.lpfnWndProc = (WNDPROC)StdWndProc;
    theJComponent->getJComponentAttr(&AWndClass);
    RegisterClass(&AWndClass);
  }

  boolean JMicroSoft::isWin32() {
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if (GetVersionEx(&osvi))
      return (osvi.dwPlatformId == VER_PLATFORM_WIN32s);
    return false;
  }

  boolean JMicroSoft::isWin95() {
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if (GetVersionEx(&osvi))
      return (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
    return false;
  }

  boolean JMicroSoft::isWinNT() {
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    if (GetVersionEx(&osvi))
      return (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT);
    return false;
  }

  #define MAXFILENAME 256

  JMicroSoft::JMicroSoft(HINSTANCE _hInstance, 
    HINSTANCE _hPrevInstance,
    LPSTR _lpszCmdLine,
    int _nCmdShow) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    hInstance = _hInstance;
    hPrevInstance = _hPrevInstance;
    lpszCmdLine = _lpszCmdLine;
    nCmdShow = _nCmdShow;

    int i, pos = 0, np;
    char szFileName[MAXFILENAME+1];
    JDList list;
    JString cmdLine(lpszCmdLine, JString::needCopy);

    GetModuleFileName(null, szFileName, 
      MAXFILENAME);
    szFileName[MAXFILENAME] = 0;
    list.append(JString(szFileName, JString::needCopy));

    for (;;) {
      np=cmdLine.indexOf(' ', pos);
      while (cmdLine[pos] == ' ') pos++;
      if (cmdLine[pos] == '"') {
	np = cmdLine.indexOf('"', ++pos);
	if (np < 0) break;
	list.append(cmdLine(pos, np++));
      } else {
	if (np < 0) {
	  if (cmdLine[pos]) list.append(cmdLine(pos));
	  break;
        } else list.append(cmdLine(pos, ++np));
      }
      pos = np;
      while (cmdLine[pos] == ' ') pos++;
    }
    JComponent::theArgString = JArray(list);
    if (!JMicroSoft::hPrevInstance)
      pClassDict->forEach(DoRegister);
    JComponentContext.add(JComponent(0));
    JComponent::theRootWindow = JComponent::getJComponent(0);
    JComponent::theRootWindow->width = rect.right;
    JComponent::theRootWindow->height = rect.bottom;
    for (i=0; i<JMAXFONT; i++)
      JFontTable.add(
        JString(JFontName[i]).toUpperCase(),
        JString(JFontInternal[i]));
    JComponent::createJWindow("JMainWindow", 
      JComponent::theRootWindow);
  }

  void JMicroSoft::DefaultLoop() {
    MSG msg;
    while (GetMessage(&msg, null, 0, 0))
      DispatchMessage(&msg);
  }

  DllImport void APIENTRY initialize_filter();
  DllImport void APIENTRY destroy_filter();

  typedef void (WINAPI *POut32)(short, short);
  typedef short (WINAPI *PInp32)(short);

  HMODULE hLibrary = (HMODULE)JComponent::loadDynLinkLibrary("inpout32.dll");
  DllExport POut32 Out32 = (POut32)GetProcAddress(hLibrary, "Out32");
  DllExport PInp32 Inp32 = (PInp32)GetProcAddress(hLibrary, "Inp32");

  int JMicroSoft::MessageLoop() {
    if (!theContextCount) return null;
    initialize_filter();
    JComponent::theMainWindow->show();
    DefaultLoop();
    destroy_filter();
    if (hLibrary != NULL) FreeLibrary(hLibrary);
    *pClassDict = JDictionary();
    return null;
  }

  #define REG_BUFFER_SIZE 256

  void RegistryUpdate(HKEY root, char* key, char* value) {
    HKEY hk;
    DWORD disposition;
    if (RegCreateKeyEx(root, key, 
      null, "", REG_OPTION_NON_VOLATILE,
      KEY_ALL_ACCESS, null, &hk, 
      &disposition) == ERROR_SUCCESS) {
      boolean needUpdate = false;
      if (disposition == REG_OPENED_EXISTING_KEY) {
        uchar data[REG_BUFFER_SIZE];
        DWORD datatype, size = REG_BUFFER_SIZE;
        if (RegQueryValueEx(hk, "", null, 
	  &datatype, data, &size) == ERROR_SUCCESS) {
	  needUpdate = (JString((char*)data) != value);
        }
      } else needUpdate = true;
      if (needUpdate) {
        RegSetValueEx(hk, "", null, 
	  REG_SZ, (uchar*)value, JString(value).length());
      }
    }
  }

  #if defined(_AWT_DLL)
    DllExport 
  #endif
  void RegisterFileType(char* type, char* name) {
    RegistryUpdate(HKEY_CLASSES_ROOT, type, name);
    RegistryUpdate(HKEY_CLASSES_ROOT, 
      JString(name)+"\\shell\\open\\command",
      *(JString*)JComponent::theArgString[0]+
	" \"%1\"");
    RegistryUpdate(HKEY_CLASSES_ROOT, 
      JString(name)+"\\shell\\open", "");
    RegistryUpdate(HKEY_CLASSES_ROOT, 
      JString(name)+"\\shell", "");
    RegistryUpdate(HKEY_CLASSES_ROOT, 
      name, JString(name)+" file");
  }

  void JComponent::idleRequest(int id) 
  { PostMessage((HWND)handle, UM_IDLE, id, null);}

  int JComponent::peekMessage(int handle) {
    MSG msg;
    while (PeekMessage(&msg, (HWND)handle, 0, 0, PM_REMOVE))
      DispatchMessage(&msg);
    return true;
  }

  int JComponent::runModal(int handle) {
    int result = CANCEL;
    MSG msg;
    while (getJComponent(handle) && GetMessage(&msg, null, 0, 0)) {
      if (((int)msg.hwnd == handle) &&
	(msg.message == WM_CLOSE)) {
	result = getJComponent(handle)->result;
      }
      DispatchMessage(&msg);
    }
    return result;
  }

  void JComponent::debug(JString text) {
    static JArray content;
    if (theMainWindow) {
      content.append(text);
      PostMessage((HWND)(int)*theMainWindow,
        UM_DEBUG, content.size(), (DWORD)(char*)text);
    }
  }

  void JComponent::_reshape_(int _x, int _y, int w, int h) { 
    if ((parent == theRootWindow)) {
      int bx, by, dy;
      if (withCaption) {
        bx = (resizable) ?  
          GetSystemMetrics(SM_CXSIZEFRAME) : 
          GetSystemMetrics(SM_CXFIXEDFRAME);
        by = (resizable) ? 
	  GetSystemMetrics(SM_CYSIZEFRAME) : 
          GetSystemMetrics(SM_CYFIXEDFRAME);
        dy = by+GetSystemMetrics(SM_CYCAPTION);
      } else {
        bx = (resizable) ? GetSystemMetrics(SM_CXFIXEDFRAME) : 0;
        dy = by = (resizable) ? GetSystemMetrics(SM_CYFIXEDFRAME) : 0;
      }
      MoveWindow((HWND)handle, _x-bx, _y-dy, 
	w+bx+bx, h+dy+by, true);
    } else MoveWindow((HWND)handle, _x, _y, w, h, true);
  }

  void JComponent::_show_(boolean cond) { 
    ShowWindow((HWND)handle, (cond) ? SW_SHOW : SW_HIDE);
  }

  void JComponent::_enable_(boolean cond)
  { EnableWindow((HWND)handle, cond);}

  boolean JComponent::_is_enabled_()
  { return (boolean)IsWindowEnabled((HWND)handle);}

  boolean JComponent::_is_visible_()
  { return (GetWindowLong((HWND)handle, GWL_STYLE) & WS_CHILD) != 0;}

  int JComponent::_get_focus_()
  { return (int)GetFocus();}

  void JComponent::_set_focus_()
  { SetFocus((HWND)handle);}

  JString JComponent::_get_text_() {
    JBlock buf(MAXTITLESIZE, 0);
    GetWindowText((HWND)handle, buf, MAXTITLESIZE);
    return JString(buf);
  }

  void JComponent::_set_text_(JString& text) 
  { SetWindowText((HWND)handle, text);}

  int JComponent::_get_dc_()
  { return (int)GetDC((HWND)handle);}

  void JComponent::_release_dc_(int hdc)
  { ReleaseDC((HWND)handle, (HDC)hdc);}

  void JComponent::_repaint_(int x, int y, int width, int height, boolean update) {
    RECT rect = { x, y, x+width, y+height};
    InvalidateRect((HWND)handle, &rect, false);
    if (update) UpdateWindow((HWND)handle);
  }

  void JComponent::_repaint_(JRegion rgn, boolean update) { 
    InvalidateRgn((HWND)handle, (HRGN)(int)rgn, false);
    if (update) UpdateWindow((HWND)handle);
  }

  void JComponent::_update_invalid_area_() 
  { UpdateWindow((HWND)handle);}

  void JComponent::_destroy_() {
    PostMessage((HWND)handle, WM_CLOSE, 0, 0L);
  }

  void JComponent::_kill_() {
    DestroyWindow((HWND)handle);
  }

  void JComponent::_raise_window_() {
    SetForegroundWindow((HWND)handle);
    SetWindowPos((HWND)handle, HWND_TOP,
      0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }

  void JComponent::_bottom_window_() {
    SetWindowPos((HWND)handle, HWND_BOTTOM,
      0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }

  void JComponent::_top_most_window_() {
    SetWindowPos((HWND)handle, HWND_TOPMOST,
      0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }

  void JComponent::_non_top_most_window_() {
    SetWindowPos((HWND)handle, HWND_NOTOPMOST,
      0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
  }

  void JComponent::_set_parent_(JComponent& parent) {
    SetParent((HWND)handle, (HWND)parent.handle);
  }

  JArray JComponent::_get_children_() {
    JArray list;
    HWND child = GetWindow((HWND)handle, GW_CHILD);
    HWND last = child;
    while (child) {
      list.add(JPObject(getJComponent((int)child)));
      child = GetWindow(child, GW_HWNDNEXT);
      if (child == last) break;
    }
    return list;
  }

  boolean JComponent::_has_child_() {
    return (GetWindow((HWND)handle, GW_CHILD) != null);
  }

  void JComponent::_set_mouse_pos_(int x, int y)
  { SetCursorPos(x, y);}

  void JComponent::getJComponentAttr(void* ptr) {
    WNDCLASS &AWndClass = *(WNDCLASS*)ptr;
    AWndClass.hIcon         = LoadIcon(JMicroSoft::hInstance, MAKEINTRESOURCE(1));
    AWndClass.hCursor       = LoadCursor(null, IDC_ARROW);
    AWndClass.hbrBackground = null;
    AWndClass.lpszMenuName  = null;
    AWndClass.lpszClassName = className();
    AWndClass.style         = null;
  }

#else

  #include <X11/Xatom.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <pthread.h>

  JHashTable JUNIX::JObjectCache(101);
  int        JUNIX::theCounter = false;
  Display*   JUNIX::theDisplay;
  Visual*    JUNIX::theVisual;
  Colormap   JUNIX::theColormap;
  int        JUNIX::theScreen;
  int	     JUNIX::theVisualDepth;
  int	     JUNIX::theEventMask;
  int	     JUNIX::theDisableMask;
  int	     JUNIX::argc;
  char**     JUNIX::argv;
  char       JEvent::keyMap[32];

  char* JFontInternal[] = {
    "courier",
    "fixed",
    "helvetica",
    "new century schoolbook",
    "terminal",
    "times"
  };

  void JComponent::setMinimized() {}
  boolean JComponent::getMinimized() { return false;}
  void JComponent::setMaximized() {}
  boolean JComponent::getMaximized() { return false;}
  void JComponent::setRestored() {}
  boolean JComponent::getRestored() { return true;}

  void JComponent::setup(int _handle, int _parent) {
    handle = _handle;
    parent = getJComponent(_parent);
    enabled = _is_enabled_();
    visible = _is_visible_();
    XSetWindowAttributes xswa;
    xswa.background_pixmap = None;
    xswa.border_pixmap = None;
    xswa.bit_gravity = NorthWestGravity;
    xswa.event_mask = JUNIX::theEventMask;
    XChangeWindowAttributes(JUNIX::theDisplay, handle,
      CWBackPixmap | CWBorderPixmap | CWEventMask | CWBitGravity, &xswa);
    x = 0;
    y = 0;
    width = 1;
    height = 1;
  }

  void JComponent::setResizable(boolean _resizable) {
    XSizeHints   XSH;
    if (resizable == _resizable) return;
    resizable = _resizable;
/*
    XSH.flags = (PMinSize | PMaxSize);
    if (resizable) {
      XSH.min_width = 1;
      XSH.min_height = 1;
      XSH.min_width = 0xFFFF;
      XSH.min_height = 0xFFFF;
    } else {
      XSH.min_width = width;
      XSH.min_height = height;
      XSH.min_width = width;
      XSH.min_height = height;
    }
    XSetWMNormalHints(JUNIX::theDisplay, 
      handle, &XSH);
*/
  }

  void JComponent::setCaption(boolean _withCaption) {
    if (withCaption == _withCaption) return;
    withCaption = _withCaption;
  }

  JComponent* createJUNIXWindow(char* name, JComponent *p, 
    int visible, void** arg) {
    JComponent* theJComponent =
      (JComponent*)(*pClassDict)[JString(name).toUpperCase()];
    if (theJComponent) {
      Window pid = (int)*p;
      int wid = (int)XCreateSimpleWindow(
        JUNIX::theDisplay, pid, 0, 0, 1, 1,
        0, (int)JColor::black, (int)JColor::white);
      theJComponent->setup(wid, pid);
      JComponentContext.add(*theJComponent);
      theJComponent = JComponent::getJComponent(wid);
      theJComponent->arg = arg;
      theJComponent->startup();
      theJComponent->show(visible);
      JUNIX::theCounter++;
    }   
    return theJComponent;
  }

  int JComponent::loadDynLinkLibrary(JString name) { return false;}
  void JComponent::freeDynLinkLibrary(int handle) {}

  JComponent* JComponent::createJComponent(char* name, JComponent *p, void** arg) 
  { return createJUNIXWindow(name, p, true, arg);}

  JComponent* JComponent::createJDialog(char* name, JComponent* p, 
    boolean withSysMenu, void** arg) 
  { return createJWindow(name, p, arg);}

  JComponent* JComponent::createJModal(char* name, JComponent* p, void** arg) 
  { return createJWindow(name, p, arg);}

  JComponent* JComponent::createJWindow(char* name, JComponent* p, void** arg) {
    XWMHints     XWMH;
    XSizeHints   XSH;
    XClassHint   CH;
    XWMH.flags = (InputHint|StateHint);
    XWMH.input = True;
    XWMH.initial_state = NormalState;
    XSH.flags = (PPosition | PSize | PMinSize);
    XSH.x = 0;
    XSH.y = 0;
    XSH.width = 1;
    XSH.height = 1;
    XSH.min_width = 1;
    XSH.min_height = 1;
    CH.res_name = name;
    CH.res_class = name;
    JComponent* result = createJUNIXWindow(name, p, false, arg);
    if (result) {
      char theGeom[80];
      sprintf(theGeom, "%dx%d+%d+%d", XSH.width,
        XSH.height, XSH.x, XSH.y);
      int bitmask = XGeometry(
        JUNIX::theDisplay, JUNIX::theScreen,
        theGeom, theGeom, 0,
        1, 1, 0, 0, &(XSH.x), &(XSH.y),
        &(XSH.width), &(XSH.height));
      if (bitmask & (XValue | YValue)) XSH.flags |= USPosition;
      if (bitmask & (WidthValue | HeightValue))
        XSH.flags |= USSize;
      XSetWMProperties(JUNIX::theDisplay, (int)*result, 
        null, null, JUNIX::argv, JUNIX::argc, 
        &XSH, &XWMH, &CH);
    }
    return result;
  }

  JUNIX::JUNIX(int _argc, char** _argv) {
    int i;
    char *display_name = null;
    argc = _argc;
    argv = _argv;
    if (!(theDisplay = XOpenDisplay(display_name))) {
      if (!(theDisplay = XOpenDisplay(display_name))) {
        printf("Can't open display named %s\n",
          XDisplayName(display_name));
        exit(1);
      }
    }
    JComponent::theArgString = JArray(argc);
    for (i=0; i<argc; i++) {
      JComponent::theArgString.set(i,
	JString(argv[i], JString::needCopy));
    }
    XInitThreads();
    theScreen = DefaultScreen(theDisplay);
    theVisual = DefaultVisual(theDisplay, theScreen);
    theVisualDepth = DefaultDepth(theDisplay, theScreen);
    theColormap = DefaultColormap(theDisplay, theScreen);
    theEventMask = 
      ExposureMask | StructureNotifyMask |
      ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
      EnterWindowMask | LeaveWindowMask | FocusChangeMask |
      KeyPressMask | KeyReleaseMask | KeymapStateMask;
    theDisableMask = 
      ExposureMask | StructureNotifyMask |
      PointerMotionMask |
      EnterWindowMask | LeaveWindowMask | FocusChangeMask |
      KeymapStateMask;

    Window theRoot = DefaultRootWindow(theDisplay);
    JComponentContext.add(JComponent((int)theRoot));
    JComponent::theRootWindow = JComponent::getJComponent((int)theRoot);
    JComponent::theRootWindow->width =
      DisplayWidth(theDisplay, theScreen);
    JComponent::theRootWindow->height =
      DisplayHeight(theDisplay, theScreen);

    for (i=0; i<JMAXFONT; i++) {
      JFontTable.add(JString(JFontName[i]).toUpperCase(),
        JString(JFontInternal[i]));
    }
    JComponent::createJWindow("JMainWindow", 
      JComponent::theRootWindow);
    XFlush(theDisplay);
  }

  extern boolean NumLockToggle;
  extern boolean ScrollLockToggle;

  int JEventModifier(unsigned int state, unsigned int button) {
    int result = button;
    if (state & ControlMask) result |= JEvent::CTRL_MASK;
    if (state & ShiftMask) result |= JEvent::SHIFT_MASK;
    if (state & LockMask) result |= JEvent::CAPS_MASK;
    if (NumLockToggle) result |= JEvent::NUM_MASK;
    if (ScrollLockToggle) result |= JEvent::SCROLL_MASK;
    if (JEvent::isKeyDown(
      XKeysymToKeycode(JUNIX::theDisplay, JEvent::JK_Alt))) 
      result |= JEvent::ALT_MASK;
    if (JEvent::isKeyDown(
      XKeysymToKeycode(JUNIX::theDisplay, JEvent::JK_AltR))) 
      result |= JEvent::ALT_MASK;
    return result;
  }

  #include "JThread.h"

  class JDelay : public JThread {
    public:
      JDelay(XEvent *pevent, int _ms) {
        event = *pevent;
        ms = _ms;
        event.xany.send_event = true;
        start();
      }
      void run() {
        sleep(ms);
        JComponent *c = JComponent::getJComponent(event.xany.window);
        if (c) {
          XSendEvent(JUNIX::theDisplay, event.xany.window, 
            false, JUNIX::theEventMask, &event);
        }
        yield();
        delete this;
      }
    protected:
      int ms;
      XEvent event;
  };

  void JUNIX::DispatchEvent(XEvent *ev) {
    static JPoint cp;
    if (ev->type == KeymapNotify) {
      JBlock(32, JEvent::keyMap).copy(
        JBlock(32, ev->xkeymap.key_vector));
      return;
    }
    JComponent &c = *JComponent::getJComponent(ev->xany.window);
    if (&c) {
      switch (ev->type) {
        case Expose: {
          c.clip |= JRegion(JRect(ev->xexpose.x, ev->xexpose.y,
            ev->xexpose.width, ev->xexpose.height));
          if (!ev->xexpose.count) c._update_window_();
          break;
        }
	case GraphicsExpose: {
          c.clip |= JRegion(JRect(ev->xgraphicsexpose.x,
            ev->xgraphicsexpose.y,
            ev->xgraphicsexpose.width,
            ev->xgraphicsexpose.height));
          if (!ev->xgraphicsexpose.count) c._update_window_();
	  break;
        }
        case ConfigureNotify: {
          c.x = ev->xconfigure.x;
          c.y = ev->xconfigure.y;
          if ((ev->xconfigure.width != c.width) ||
            (ev->xconfigure.height != c.height)) {
            c.width = ev->xconfigure.width;
            c.height = ev->xconfigure.height;
            c.layout();
          }
          break;
        }
        case ClientMessage: {
          if (ev->xclient.data.l[0] == ClientMessage)
            c.idleAction(ev->xclient.data.l[1]);
          break;
        }
        case DestroyNotify: {
          if (!ev->xany.send_event) {
            c.destroy();
            theCounter--;
            JComponentContext.del(c);
          } else c.kill();
          break;
        }
        case MapNotify:
          c.layoutRestored();
          break;
        case UnmapNotify:
          c.layoutMinimized();
          break;
        case ButtonPress: {
          if (ev->xany.send_event) {
  	    JMouseDrag &= ~JEvent::BUTTONS;
            boolean needAction = false;
            switch (ev->xbutton.button) {
              case Button1: 
	        JMouseDrag |= JEvent::LBUTTON;
                needAction = (JMouseDrag & JEvent::LBUTTON_MASK) != 0;
	        break;
              case Button2: 
	        JMouseDrag |= JEvent::MBUTTON;
                needAction = (JMouseDrag |= JEvent::MBUTTON_MASK) != 0;
	        break;
              case Button3: 
	        JMouseDrag |= JEvent::RBUTTON; 
                needAction = (JMouseDrag |= JEvent::RBUTTON_MASK) != 0;
	        break;
            }
            if (needAction) {
              JEvent event(&c,
                JEvent::MOUSE_ACTION,
                cp.x, cp.y, 0,
                JEventModifier(ev->xbutton.state, JMouseDrag));
              c.postJEvent(event);
              new JDelay(ev, 100);
            }
          } else {
	    JMouseDrag &= ~JEvent::BUTTONS;
            switch (ev->xbutton.button) {
              case Button1: 
	        JMouseDrag |= JEvent::LBUTTON; 
	        JMouseDrag |= JEvent::LBUTTON_MASK; 
	        break;
              case Button2: 
	        JMouseDrag |= JEvent::MBUTTON;
	        JMouseDrag |= JEvent::MBUTTON_MASK; 
	        break;
              case Button3: 
	        JMouseDrag |= JEvent::RBUTTON; 
	        JMouseDrag |= JEvent::RBUTTON_MASK; 
	        break;
            }
            JEvent event(&c,
              JEvent::MOUSE_DOWN,
              cp.x = ev->xbutton.x, cp.y = ev->xbutton.y, 0,
              JEventModifier(ev->xbutton.state, JMouseDrag));
            if ((event.when > lastClkTime) && 
              (event.when-lastClkTime < 300))
              event.modifiers |= JEvent::DBCLK_MASK;
            lastClkTime = event.when;
            c.postJEvent(event);
//            new JDelay(ev, 500);
          }
	  break;
        }
        case ButtonRelease: {
	  JMouseDrag &= ~JEvent::BUTTONS;
          switch (ev->xbutton.button) {
            case Button1: 
	      JMouseDrag |= JEvent::LBUTTON; 
	      JMouseDrag &= ~JEvent::LBUTTON_MASK; 
	      break;
            case Button2: 
	      JMouseDrag |= JEvent::MBUTTON; 
	      JMouseDrag &= ~JEvent::MBUTTON_MASK; 
	      break;
            case Button3: 
	      JMouseDrag |= JEvent::RBUTTON; 
	      JMouseDrag &= ~JEvent::RBUTTON_MASK; 
	      break;
          }
          JEvent event(&c,
            JEvent::MOUSE_UP,
            cp.x = ev->xbutton.x, cp.y = ev->xbutton.y, 0,
            JEventModifier(ev->xbutton.state, JMouseDrag));
          c.postJEvent(event);
          break;
        }
        case EnterNotify: {
          JEvent event(&c,
            JEvent::MOUSE_ENTER,
            ev->xcrossing.x, ev->xcrossing.y, 0,
            JEventModifier(ev->xcrossing.state, JMouseDrag));
          c.postJEvent(event);
          break;
        }
        case LeaveNotify: {
          JEvent event(&c,
            JEvent::MOUSE_EXIT,
            cp.x = ev->xcrossing.x, cp.y = ev->xcrossing.y, 0,
            JEventModifier(ev->xcrossing.state, JMouseDrag));
          c.postJEvent(event);
          break;
        }
        case MotionNotify: {
	  JMouseDrag &= ~JEvent::BUTTONS;
          JEvent event(&c,
            ((JMouseDrag) ? JEvent::MOUSE_DRAG : JEvent::MOUSE_MOVE),
            cp.x = ev->xmotion.x, cp.y = ev->xmotion.y, 0,
            JEventModifier(ev->xmotion.state, JMouseDrag));
          c.postJEvent(event);
          break;
        }
        case FocusIn: {
          static JComponent *lastFocus = null;
          if (lastFocus == &c) break;
          if (lastFocus && JComponent::getJComponent((int)*lastFocus)) {
            JEvent event(lastFocus, JEvent::LOST_FOCUS);
            event.arg = &c;
            lastFocus->postJEvent(event);
          } else lastFocus = null;
          JEvent event(&c, JEvent::GOT_FOCUS);
	  event.arg = lastFocus;
          lastFocus = &c;
          c.postJEvent(event);
          break;
        }
        case KeyPress:
        case KeyRelease: {
          int id = 0;
          if (ev->type == KeyRelease) {
            id = JEvent::KEY_RELEASE;
            if (XEventsQueued(theDisplay, QueuedAfterReading)) {
              XEvent nev;
              XPeekEvent(theDisplay, &nev);
              if ((nev.type == KeyPress) && 
                (nev.xkey.time == ev->xkey.time)) {
                XNextEvent(theDisplay, ev);
                id = JEvent::KEY_ACTION;
              }
            } else JEvent::setKeyState(ev->xkey.keycode, false);
          } else {
            id = JEvent::KEY_PRESS;
            JEvent::setKeyState(ev->xkey.keycode, true);
          }
          KeySym ks;
          XComposeStatus cs;
          char buffer[10];
          XLookupString(&ev->xkey, buffer, 10, &ks, &cs);
          if (id == JEvent::KEY_PRESS) {
            switch (ks) {
              case JEvent::JK_Num_Lock:
                NumLockToggle = !NumLockToggle;
                break;
              case JEvent::JK_Scroll_Lock:
                ScrollLockToggle = !ScrollLockToggle;
                break;
            }
          }
          JEvent event(&c,
            id,	ev->xkey.x, ev->xkey.y, JEvent::VKtoJK(ks), 
            JEventModifier(ev->xkey.state, JMouseDrag), 1);
          c.postJEvent(event);
          break;
        }
      }
    }
  }

  int lcount = 0;

  void JUNIX::DefaultLoop() {
    XEvent event;
    while (JUNIX::theCounter) {
      XNextEvent(JUNIX::theDisplay, &event);
      DispatchEvent(&event);
    }
  }

  int JUNIX::MessageLoop() {
    XEvent event;
    if (!JComponent::theMainWindow) return 0;
    JComponent::theMainWindow->show();
    DefaultLoop();
    XCloseDisplay(JUNIX::theDisplay);
    *pClassDict = JDictionary();
    return 0;
  }

  void JComponent::idleRequest(int id) { 
    XEvent event;
    event.xany.type = ClientMessage;
    event.xany.display = JUNIX::theDisplay;
    event.xany.window = handle;
    event.xclient.message_type = null;
    event.xclient.format = 32;
    event.xclient.data.l[0] = ClientMessage;
    event.xclient.data.l[1] = id;
    XSendEvent(JUNIX::theDisplay, event.xany.window, 
        false, null, &event);
    XFlush(JUNIX::theDisplay);
  }

  int JComponent::peekMessage(int handle) {
    int result = null;
    XEvent event;
    int pending = XEventsQueued(JUNIX::theDisplay, QueuedAfterReading);
    while (pending-- && !result) {
      XNextEvent(JUNIX::theDisplay, &event);
      if ((event.xany.type == DestroyNotify) &&
        (event.xany.send_event)) {
        XSendEvent(JUNIX::theDisplay, event.xany.window, 
         false, null, &event);
        continue;
      }
      JUNIX::DispatchEvent(&event);
    }
    return result;
  }

  int JComponent::runModal(int handle) {
    XEvent event;
    while (getJComponent(handle)) {
      XPeekEvent(JUNIX::theDisplay, &event);
      if (event.xany.window == handle &&
        (event.type == DestroyNotify)) {
        return getJComponent(handle)->result;
      }
      XNextEvent(JUNIX::theDisplay, &event);
      JUNIX::DispatchEvent(&event);
    }
    return null;
  }

  void JComponent::debug(JString text) {
    printf("%s\n", (char*)text);
  }

  class JEventCell : public JObject {
    public:
      JEventCell(XEvent _event); 
      XEvent event;
  };
    
  JEventCell::JEventCell(XEvent _event) { event = _event;}

  void waitGraphicsExpose(int handle) {
    boolean match;
    boolean finish = false;
    XEvent event;
    JArray queue;
    while (!finish) {
      XNextEvent(JUNIX::theDisplay, &event);
      if (event.xany.window == handle) { 
        switch (event.type) {
          case NoExpose:
            match = true;
            finish = true;
            break;  
          case GraphicsExpose:
            match = true;
            if (!event.xgraphicsexpose.count)
              finish = true;
            break;
          default:
            match = false;
        }
      } else match = false;
      if (!match) queue.append(JEventCell(event));
      else JUNIX::DispatchEvent(&event);
    }
    int sz = queue.size();
    for (int i=0; i<sz; i++)
      JUNIX::DispatchEvent(
        &((JEventCell*)queue[i])->event);
  }

  void waitWindowDestroy(int handle) {
    boolean match = false;
    XEvent event;
    int pending = XEventsQueued(JUNIX::theDisplay, QueuedAfterReading);
    while (pending-- && !match) {
      XNextEvent(JUNIX::theDisplay, &event);
      if (event.type == DestroyNotify) {
        if (event.xany.send_event) {
          XSendEvent(JUNIX::theDisplay, event.xany.window, 
           false, null, &event);
          continue;
        }
        if (event.xany.window == handle)
          match = true;
      }
      JUNIX::DispatchEvent(&event);
    }
  }

  void JComponent::_reshape_(int _x, int _y, int w, int h) {
    if ((x == _x) && (y == _y)) {
      XResizeWindow(JUNIX::theDisplay, (Window)handle,
        w=max(1, w), h=max(1, h));
    } else {
      XMoveResizeWindow(JUNIX::theDisplay, (Window)handle,
        _x, _y, w=max(1, w), h=max(1, h));
      x = _x;
      y = _y;
    }
    if ((width != w) || (height != h)) {
      width = w;
      height = h;
      layout();
    }
  }

  void JComponent::_show_(boolean cond) {
    if (cond) XMapWindow(JUNIX::theDisplay, (Window)handle);
    else XUnmapWindow(JUNIX::theDisplay, (Window)handle);
  }

  void JComponent::_enable_(boolean cond) {
    XSetWindowAttributes xswa;
    xswa.event_mask = (cond) ? 
      JUNIX::theEventMask : JUNIX::theDisableMask;
    XChangeWindowAttributes(JUNIX::theDisplay, handle,
      CWEventMask, &xswa);
  }

  boolean JComponent::_is_enabled_() {
    XWindowAttributes xwa;
    XGetWindowAttributes(JUNIX::theDisplay, handle, &xwa);
    return xwa.your_event_mask == JUNIX::theEventMask;
  }

  boolean JComponent::_is_visible_() { return false;}

  int JComponent::_get_focus_() { 
    Window focus;
    int revert_to;
    XGetInputFocus(JUNIX::theDisplay, &focus, &revert_to);
    return focus;
  }

  void JComponent::_set_focus_() {
    peekMessage();
    XSetInputFocus(JUNIX::theDisplay, (Window)handle, 
      RevertToParent, CurrentTime);
  }

  JString JComponent::_get_text_() {
    if (parent == theRootWindow) {
      int count;
      char** list;
      XTextProperty WName;
      if (XGetWMName(JUNIX::theDisplay, (Window)handle, &WName)) {
        XTextPropertyToStringList(&WName, &list, &count);
        if (count > 0) return JString(list[0]);
      }
    }
    return JString();
  }

  void JComponent::_set_text_(JString& text) {
    if (parent == theRootWindow) {
      XTextProperty WName;
      char *str = (char*)text;
      XStringListToTextProperty(&str, 1, &WName);
      XSetWMName(JUNIX::theDisplay, (Window)handle, &WName);
      XSetWMIconName(JUNIX::theDisplay, (Window)handle, &WName);
    }
  }

  int JComponent::_get_dc_() {
    return (int)XCreateGC(JUNIX::theDisplay, (Window)handle, 0, null);
  }

  void JComponent::_release_dc_(int hdc) 
  { XFreeGC(JUNIX::theDisplay, (GC)hdc);}

  void JComponent::_repaint_(int x, int y, int width, int height, boolean update) { 
    if (!update) {
      XClearArea(JUNIX::theDisplay, (Window)handle, 
        x, y, width, height, true);
    } else {
      clip |= JRegion(x, y, width, height);
      _update_window_();
    }
    XFlush(JUNIX::theDisplay);
  }

  void JComponent::_repaint_(JRegion rgn, boolean update) {
    if (!update) {
      JRect rect = (JRect)rgn;
      XClearArea(JUNIX::theDisplay, (Window)handle, 
        rect.x, rect.y, rect.width, rect.height, true);
    } else {
      clip |= rgn;
      _update_window_();
    }
    XFlush(JUNIX::theDisplay);
  }

  void JComponent::_update_invalid_area_() {
    XFlush(JUNIX::theDisplay);
  }

  void JComponent::_update_window_() {
    JRect rect = (JRect)clip;
    if (rect.isEmpty()) return;
    beforePaint(&rect);
    JGraphics g = getJGraphics();
    g.setJRegion(clip);
    if (useImage()) {
      JImage image(width, height);
      JGraphics bg = image.getJGraphics(*this);
      bg.setJRegion(clip);
      paint(bg);
      bg.Release();
      g.drawJImage(image, 0, 0);
    } else paint(g);
    g.Release();
    afterPaint(&rect);
    clip = JRegion();
  }

  void JComponent::_destroy_() {
    JEvent event(this,
      JEvent::WINDOW_CLOSE_QUERY);
    if (!postJEvent(event)) return;
    XEvent ev;
    ev.xany.type = DestroyNotify;
    ev.xany.display = JUNIX::theDisplay;
    ev.xany.window = handle;
    XSendEvent(JUNIX::theDisplay, ev.xany.window, 
      false, null, &ev);
  }

  void JComponent::_kill_() {
    JArray item = getChildren();
    int size = item.size();
    for (int i=0; i<size; i++)
      ((JComponent*)OPTR(item[i]))->_kill_();
    destroy();
    JUNIX::theCounter--;
    XDestroyWindow(JUNIX::theDisplay, handle);
    JComponentContext.del(*this);
    waitWindowDestroy(handle);
  }
          
  void JComponent::_raise_window_() 
  { XRaiseWindow(JUNIX::theDisplay, (Window)handle);}
          
  void JComponent::_bottom_window_() {}

  void JComponent::_top_most_window_() {}

  void JComponent::_non_top_most_window_() {}

  void JComponent::_set_parent_(JComponent& parent) {
    XReparentWindow(JUNIX::theDisplay, (Window)handle, 
      (Window)parent.handle, x, y);
  }

  JArray JComponent::_get_children_() {
    JArray result;
    unsigned int nchildren;
    Window root, parent, *children;
    if (XQueryTree(JUNIX::theDisplay, (Window)handle,
      &root, &parent, &children, &nchildren)) {
      for (int i=0; i<nchildren; i++)
	result.append(JPObject(getJComponent(children[i])));
    }
    return result;
  }

  boolean JComponent::_has_child_() {
    unsigned int nchildren;
    Window root, parent, *children;
    if (XQueryTree(JUNIX::theDisplay, (Window)handle,
      &root, &parent, &children, &nchildren)) {
      return (nchildren > 0);
    }
    return false;
  }

  void JComponent::_set_mouse_pos_(int _x, int _y) {
    XWarpPointer(JUNIX::theDisplay, 
      (int)*theRootWindow, (int)*theRootWindow, 
      theRootWindow->x, theRootWindow->y,
      theRootWindow->width, theRootWindow->height,
      _x, _y);
  }

#endif

