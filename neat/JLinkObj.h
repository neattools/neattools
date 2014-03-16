#if !defined( _JLinkObj_h )
#define _JLinkObj_h

#include "JViewSet.h"
#include "JModuleObj.h"

class
#include "JNEAT.hpp"
JLinkObj : public JViewSet {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { LEFT, TOP, RIGHT, BOTTOM};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JLinkObj();
    JLinkObj(JModuleObj* _from, int _fn, JModuleObj* _to, int _tn, double _pos);
    virtual JString info();
    virtual JFPoint& translate(double dx, double dy);
    virtual void rescale(JFRect& info, double wscale, double hscale);
    virtual void remove();
    virtual JFRect calculateExtent();
    virtual void fixPointer(JDictionary& dict);
    void addSelf();
    void access(const JDataType& data);
    void engine();
    boolean cond();
    JModuleObj *from, *to;
    double pos;
    int fn, tn;
};

#endif
