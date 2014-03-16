#if !defined( _JRect_h )
#define _JRect_h

#include "JPoint.h"
#include "JDimension.h"

class
#include "JAWT.hpp"
JRect : public JPoint {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JRect();
    JRect(int width, int height);
    JRect(int x, int y, int width, int height);
    JRect(const JPoint& p);
    JRect(const JDimension& d);
    JRect(const JPoint& p, const JDimension& d);
    JRect(const JPoint& p1, const JPoint& p2);
    JPoint location();
    JPoint center();
    JDimension size();
    boolean isEmpty() const;
    boolean inside(int x, int y);
    boolean inside(const JRect& r);
    boolean operator&&(const JRect& r);
    boolean operator||(const JRect& r);
    JRect operator&(const JRect& r);
    JRect operator|(const JRect& r);
    JRect operator|(const JPoint& r);
    JRect& operator&=(const JRect& r);
    JRect& operator|=(const JRect& r);
    JRect& operator|=(const JPoint& r);
    virtual JRect& reshape(int _x, int _y, int _width, int _height);
    virtual JRect& reshape(JRect r);
    JRect& resize(int width, int height);
    JRect& resize(JDimension d);
    JRect& normalize();
    JRect& growBy(int h, int v);
    JRect& shrinkBy(int h, int v);
    JRect grow(int h, int v);
    JRect shrink(int h, int v);
    int width, height;
};

#endif
