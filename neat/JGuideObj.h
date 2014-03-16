#if !defined( _JGuideObj_h )
#define _JGuideObj_h

#include "JViewObj.h"
#include "JList.h"

class
#include "JNEAT.hpp"
JGuideObj : public JViewObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum {HORIZONTAL, VERTICAL};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JGuideObj();
    JGuideObj(int _type, double pos, double vmin, double vmax);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual JFPoint& translate(double dx, double dy);
    virtual void rescale(JFRect& info, double wscale, double hscale);
    virtual JString info();
  protected:
    int type;
};

#endif
