#if !defined( _JHPCounterObj_h )
#define _JHPCounterObj_h

#include "JModuleObj.h"
#include "int64.h"

class JHPCounterObj : public JModuleObj {
  public:
    enum { IN_TRIGGER, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JHPCounterObj();
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect inputArea(int n);
    virtual int inputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
  protected:
    double value;
    int64 baseCount;
    static int baseFrequency;
};

#endif
