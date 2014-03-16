#if !defined( _JFocusObj_h )
#define _JFocusObj_h

#include "JBtnObj.h"

class JFocusObj : public JBtnObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JFocusObj();
    virtual void startup();
    virtual boolean gotFocus(JEvent& e);
    virtual boolean lostFocus(JEvent& e);
    virtual void engine(int n, JLinkObj& link);
};

#endif
