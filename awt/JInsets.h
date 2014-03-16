#if !defined( _JInsets_h )
#define _JInsets_h

#include "JObject.h"

class
#include "JAWT.hpp"
JInsets : public JObject {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JInsets();
    JInsets(int thickness);
    JInsets(int left, int top, int right, int bottom);
    int left, top, right, bottom;
};

#endif
