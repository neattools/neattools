#if !defined( _JLineObj_h )
#define _JLineObj_h

#include "JViewObj.h"
#include "JList.h"

class
#include "JNEAT.hpp"
JLineObj : public JViewObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JLineObj();
    JLineObj(JFPoint& _sp, JFPoint& _ep);
    double getDistance(JFPoint pt);
    virtual void nearest(double x, double y, double& d, JViewObj*& dest);
    virtual void touch(JFRect& r, class JFocusSet& set);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual JFPoint& translate(double dx, double dy);
    virtual void rescale(JFRect& info, double wscale, double hscale);
  protected:
    JFPoint sp, ep;
};

#endif
