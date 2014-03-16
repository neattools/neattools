#if !defined( _JPoint_h )
#define _JPoint_h

#include "JObject.h"

class
#include "JAWT.hpp"
JPoint : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JPoint();
    JPoint(int x, int y);
    int distance(JPoint pt);
    JPoint& move(int x, int y);
    JPoint& translate(int dx, int dy);
    int x, y;
};

#endif
