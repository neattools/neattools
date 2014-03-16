#if !defined( _JViewObj_h )
#define _JViewObj_h

#include "JFRect.h"
#include "JGraphics.h"
#include "JEvent.h"
#include "JRegion.h"
#include "JDictionary.h"
#include "JProperty.h"

class
#include "JNEAT.hpp"
JViewObj : public JFRect {
  public:
    enum {
      KEYBOARD_MASK = 0x0001,
      MOUSE_MASK = 0x0002,
      GLOBAL_KEYBOARD_MASK = 0x0004,
      GLOBAL_MOUSE_MASK = 0x0008,
      FOCUS_MASK = 0x0010,
      MIXER_MASK = 0x0020
    };
    static double delta;
    class JViewSet *parent;
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    virtual void forEachNode(iterFuncType, void** arg=null) const;
    virtual JObject* firstNodeThat(condFuncType, void** arg=null) const;
    virtual JObject* lastNodeThat(condFuncType, void** arg=null) const;
    JViewObj();
    boolean needEvent(int mask);
    virtual int getEventMask();
    virtual JRegion getJRegion();
    virtual void toFront();
    virtual void toBack();
    virtual void remove();
    virtual void startup();
    virtual void reset();
    virtual void close();
    JFPoint calculateOffset();
    virtual void ungroup(class JViewSet& np, class JFocusSet& set);
    virtual JViewObj* locate(double x, double y, JViewObj*& obj);
    virtual void nearest(double x, double y, double& d, JViewObj*& dest);
    virtual void selectObj(JFRect& r, class JFocusSet& set);
    virtual void touch(JFRect& r, class JFocusSet& set);
    virtual JFRect calculateExtent();
    virtual JFRect calculateUpdate();
    virtual void calculateJRegion(JRegion& rgn, double dx, double dy, double scale);
    virtual JRect getIExtent(double dx, double dy, double scale);
    virtual JPoint getIPoint(JFPoint pt, double dx, double dy, double scale);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& clip, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& clip, double scale);
    virtual JString info();
    virtual void rescale(JFRect& info, double wscale, double hscale);
    virtual JViewObj* duplicate(class JViewSet* _parent = null, JDictionary* dict = null);
    virtual void duplicateCheck(JDictionary& dict);
    virtual void fixParent(class JViewSet* _parent = null);
    virtual void fixPointer(JDictionary& dict);
    virtual void toHash(JHashTable& hash);
    virtual boolean handleJEvent(JEvent& e);
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseMove(JEvent& e, double x, double y);
    virtual boolean mouseDrag(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean keyUp(JEvent& e, int key);
    virtual boolean globalMouseDown(JEvent& e, int x, int y);
    virtual boolean globalMouseMove(JEvent& e, int x, int y);
    virtual boolean globalMouseUp(JEvent& e, int x, int y);
    virtual boolean globalKeyDown(JEvent& e, int key);
    virtual boolean globalKeyUp(JEvent& e, int key);
    virtual boolean gotFocus(JEvent& e);
    virtual boolean lostFocus(JEvent& e);
    virtual boolean mixerLineNotify(JEvent& e, int mid, int lid);
    virtual boolean mixerControlNotify(JEvent& e, int mid, int cid);
    virtual boolean dataNotify(JEvent& e, void* data);
    virtual boolean auxNotify(JEvent& e, void* data);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean propertyDialog(int x, int y);
    virtual boolean isOpaque();
  protected:
    void transform(double& v, JFRect& info, double wscale, double hscale);
    void transform(JFPoint& pt, JFRect& info, double wscale, double hscale);
};

#endif
