#if !defined( _J1DMeterObj_h )
#define _J1DMeterObj_h

#include "JNBitsObj.h"

class J1DMeterObj : public JNBitsObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { HORIZONTAL, VERTICAL};
    virtual const char* className() const;
    virtual JObject* clone() const;
    J1DMeterObj(int _type = HORIZONTAL);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual boolean cond(int n, JLinkObj& link);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JFRect outputArea(int n);
    virtual int outputFace(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual double outputPos(int n, JFPoint opt);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean setValue(int _value);
    virtual void addButton(JComponent *panel);
  protected:
    int oValue;
    int type;
};

#endif
