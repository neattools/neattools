#if !defined( _JFPoint_h )
#define _JFPoint_h

#include "JObject.h"

class
#include "JNEAT.hpp"
JFPoint : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFPoint();
    JFPoint(double x, double y);
    double distance(JFPoint pt);
    virtual JFPoint& move(double x, double y);
    virtual JFPoint& translate(double dx, double dy);
    double x, y;
};

#endif
