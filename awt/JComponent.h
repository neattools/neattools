#if !defined( _JComponent_h )
#define _JComponent_h

#include "JRect.h"
#include "JColor.h"
#include "JFont.h"
#include "JRegion.h"
#include "JEvent.h"
#include "JInsets.h"
#include "JGraphics.h"
#include "JFontMetrics.h"
#include "JArray.h"
#include "JLayoutManager.h"

class
#include "JAWT.hpp"
JComponent : public JRect {
  public:
    enum { CANCEL = 1, OK = 2, NO = 4, YES = 8};
    static JComponent* theMainWindow;
    static JComponent* theRootWindow;
    static JArray theArgString;
    static int maxFontList();
    static char** getFontList();
    static JComponent* getJComponent(int handle);
    static int peekMessage(int handle = null);
    static int runModal(int handle);
    static int loadDynLinkLibrary(JString name);
    static void freeDynLinkLibrary(int handle);
    static JComponent* createJComponent(char* name, JComponent* p, void** arg = null);
    static JComponent* createJWindow(char* name, JComponent* p, void** arg = null);
    static JComponent* createJDialog(char* name, JComponent* p, 
      boolean widthSysMenu = true, void** arg = null);
    static JComponent* createJModal(char* name, JComponent* p, void** arg = null);
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual boolean isWindow() const;
    virtual int hashCode() const;
    virtual int compareTo(const JObject& s) const;
#if defined(WIN32)
    virtual void getJComponentAttr(void* ptr);
#endif
    JComponent();
    JComponent(int handle, JComponent* _source = null);
    operator int() const;
    JComponent* getParent();
    JComponent* getTopParent();
    void setParent(JComponent& parent);
    boolean hasChild();
    JArray getChildren();
    void add(JComponent& child, int pos=-1);
    void add(int type, JComponent& child);
    void remove(JComponent& child);
    void removeAll();
    JLayoutManager getLayout();
    void setLayout(JLayoutManager& mgr);
    void setup(int _handle, int _parent);
    void setResizable(boolean resizable);
    void setCaption(boolean withCaption);
    boolean isVisible();
    boolean isEnabled();
    boolean isAncestor(JComponent& ancestor);
    boolean isFocusOn();
    JRect bounds();
    void enable(boolean cond);
    void show(boolean cond);
    virtual void enable();
    virtual void disable();
    virtual void show();
    virtual void hide();
    virtual void setText(JString text);
    JString getText();
    JColor getForeground();
    void setForeground(JColor c);
    JColor getBackground();
    void setBackground(JColor c);
    JFont getJFont();
    void setJFont(JFont f);
    void move(int x, int y);
    virtual JRect& reshape(int x, int y, int width, int height);
    virtual JRect& reshape(JRect rect);
    virtual JInsets insets();
    virtual JDimension preferredSize();
    virtual JDimension minimumSize();
    virtual void startup();
    virtual void layout();
    virtual void setMinimized();
    virtual boolean getMinimized();
    virtual void setMaximized();
    virtual boolean getMaximized();
    virtual void setRestored();
    virtual boolean getRestored();
    virtual void layoutMinimized();
    virtual void layoutMaximized();
    virtual void layoutRestored();
    virtual void destroy();
    virtual void dispose();
    virtual void kill();
    virtual void activate();
    virtual void deactivate();
    virtual void idleAction(int id);
    void idleRequest(int id);
    void toFront();
    void toBack();
    void toTopMost();
    void toNonTopMost();
    JGraphics getJGraphics();
    virtual void beforePaint(JRect *rect = null);
    virtual void afterPaint(JRect *rect = null);
    virtual void paint(JGraphics g);
    void repaint(boolean update=false);
    void repaint(JRect r, boolean update=false);
    void repaint(JRegion rgn, boolean update=false);
    void repaint(int x, int y, int width, int height, boolean update=false);
    void updateInvalidArea();
    void ScrollWindow(int x, int y, int width, int height, int dx, int dy);
    JComponent* locate(int x, int y);
    void setMousePos(int x, int y);
    void translateJEvent(JEvent& e, JComponent* dest);
    void reverseJEvent(JEvent& e, JComponent* dest);
    virtual boolean postJEvent(JEvent& e);
    virtual boolean handleJEvent(JEvent& e);
    virtual boolean mouseEnter(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual boolean mouseMove(JEvent& e, int x, int y);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseDrag(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean keyUp(JEvent& e, int key);
    virtual boolean action(JEvent& e, JObject* arg);
    virtual boolean gotFocus(JEvent& e, JObject* arg);
    virtual boolean lostFocus(JEvent& e, JObject* arg);
    virtual boolean childNotify(JEvent& e, JObject* arg);
    virtual boolean parentNotify(JEvent& e, JObject* arg);
    virtual boolean peerNotify(JEvent& e, JObject* arg);
    virtual boolean dataNotify(JEvent& e, JObject* arg);
    virtual boolean auxNotify(JEvent& e, JObject* arg);
    virtual boolean closeQuery(JEvent& e);
    virtual boolean useImage();
    virtual boolean needRedraw();
    void requestFocus();
    void nextFocus();
    static void debug(JString text);
#if !defined(WIN32)
    void _update_window_();
    JRegion clip;
#endif
    void** arg;
  protected:
    int handle, result;
    JString text;
    JComponent *parent;
    boolean enabled;
    boolean visible;
    boolean resizable;
    boolean withCaption;
    JColor *foreground;
    JColor *background;
    JFont *font;
    JLayoutManager *layoutMgr;
    void _reshape_(int x, int y, int w, int h);
    void _show_(boolean cond);
    void _enable_(boolean cond);
    boolean _is_enabled_();
    boolean _is_visible_();
    int _get_focus_();
    void _set_focus_();
    JString _get_text_();
    void _set_text_(JString& text);
    int _get_dc_();
    void _release_dc_(int hdc);
    void _repaint_(int x, int y, int width, int height, boolean update=false);
    void _repaint_(JRegion rgn, boolean update=false);
    void _update_invalid_area_();
    void _destroy_();
    void _kill_();
    void _raise_window_();
    void _bottom_window_();
    void _top_most_window_();
    void _non_top_most_window_();
    void _set_parent_(JComponent& parent);
    JArray _get_children_();
    boolean _has_child_();
    void _set_mouse_pos_(int x, int y);
};

#endif
