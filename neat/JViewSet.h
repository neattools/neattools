#if !defined( _JViewSet_h )
#define _JViewSet_h

#include "JViewObj.h"
#include "JDList.h"
#include "JComponent.h"
#include "JRegion.h"

class
#include "JNEAT.hpp"
JViewSet : public JViewObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    JComponent* root;
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    virtual void forEachNode(iterFuncType, void** arg=null) const;
    virtual void forEachChild(iterFuncType, void** arg=null) const;
    virtual JObject* firstNodeThat(condFuncType, void** arg=null) const;
    virtual JObject* firstChildThat(condFuncType, void** arg=null) const;
    virtual JObject* lastNodeThat(condFuncType, void** arg=null) const;
    virtual JObject* lastChildThat(condFuncType, void** arg=null) const;
    JViewSet(JComponent* _root = null);
    JComponent* getRoot();
    virtual int getEventMask();
    virtual void remove();
    virtual void startup();
    virtual void close();
    virtual void toFirst(JViewObj& obj);
    virtual void toLast(JViewObj& obj);
    virtual void reparent(JViewObj& obj, JViewSet& np);
    virtual void reparent(JViewSet& np);
    virtual void ungroup(JViewSet& np, JFocusSet& set);
    virtual JViewObj* add(JViewObj& obj);
    virtual void del(JViewObj& obj);
    virtual int indexOf(JViewObj& obj);
    virtual JViewObj* operator[](JViewObj& obj);
    virtual JViewObj* operator[](int index);
    virtual JViewObj* first();
    virtual JViewObj* last();
    int size() const;
    void delAll();
    void Dereference();
    boolean isEmpty();
    void addLine(double x1, double y1, double x2, double y2);
    void addRect(double x, double y, double width, double height);
    void addJFRect(JFRect rect);
    virtual JViewObj* locate(double x, double y, JViewObj*& dest);
    virtual void nearest(double x, double y, double& d, JViewObj*& dest);
    virtual JFocusSet select(JFRect& r);
    virtual void touch(JFRect& r, class JFocusSet& set);
    virtual JViewObj* nearestTouch(JFRect& r);
    virtual JFRect calculateExtent();
    virtual JFRect calculateUpdate();
    virtual JRegion getJRegion();
    virtual void calculateJRegion(JRegion& rgn, double dx, double dy, double scale);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual JString info();
    virtual JFPoint& translate(double dx, double dy);
    virtual void rescale(JFRect& info, double wscale, double hscale);
    virtual JViewObj* duplicate(JViewSet* _parent = null, JDictionary* dict = null);
    virtual void fixParent(JViewSet* _parent = null);
    virtual void fixPointer(JDictionary& dict);
    virtual void toHash(JHashTable& hash);
    virtual boolean handleJEvent(JEvent& e);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean isOpaque();
  protected:
    int eventMask;
    JDList children;
    JRegion region;
};

#endif
