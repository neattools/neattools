#if !defined( _JFocusSet_h )
#define _JFocusSet_h

#include "JViewSet.h"

class
#include "JNEAT.hpp"
JFocusSet : public JViewSet {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFocusSet();
    virtual void remove();
    virtual void ungroup(JViewSet& np, JFocusSet& set);
    virtual JViewObj* add(JViewObj& obj);
    virtual void del(JViewObj& obj);
    virtual JViewObj* operator[](JViewObj& obj);
    virtual JViewObj* operator[](int index);
    virtual JViewObj* first();
    virtual JViewObj* last();
    virtual void toFront();
    virtual void toBack();
    void toggle(JViewObj& newObj);
    void toggle(JFocusSet& newSet);
    virtual JViewObj* duplicateFocus(JViewSet& linkSet, JViewSet* _parent = null);
  protected:
    JViewObj* extract(JObject* obj);
};

#endif
