#if !defined( _JFRect_h )
#define _JFRect_h

#include "JFPoint.h"
#include "JFDimension.h"

class
#include "JNEAT.hpp"
JFRect : public JFPoint {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JFRect();
    JFRect(double width, double height);
    JFRect(double x, double y, double width, double height);
    JFRect(const JFPoint& p);
    JFRect(const JFDimension& d);
    JFRect(const JFPoint& p, const JFDimension& d);
    JFRect(const JFPoint& p1, const JFPoint& p2);
    JFPoint location();
    JFPoint center();
    JFDimension size();
    boolean isEmpty() const;
    boolean inside(double x, double y);
    boolean inside(const JFRect& r);
    boolean operator&&(const JFRect& r);
    boolean operator||(const JFRect& r);
    JFRect operator&(const JFRect& r);
    JFRect operator|(const JFRect& r);
    JFRect operator|(const JFPoint& r);
    JFRect& operator&=(const JFRect& r);
    JFRect& operator|=(const JFRect& r);
    JFRect& operator|=(const JFPoint& r);
    virtual JFRect& reshape(double _x, double _y, double _width, double _height);
    virtual JFRect& reshape(JFRect r);
    JFRect& resize(double width, double height);
    JFRect& resize(JFDimension d);
    JFRect& normalize();
    JFRect& growBy(double h, double v);
    JFRect& shrinkBy(double h, double v);
    JFRect grow(double h, double v);
    JFRect shrink(double h, double v);
    double width, height;
};

#endif
