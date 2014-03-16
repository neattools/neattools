#if !defined( _JTimeObj_h )
#define _JTimeObj_h

#include "JANDObj.h"
#include "JDate.h"
#include "JThread.h"

class JTimeObj : public JModuleObj {
  public:
    enum { IN_TRIGGER, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    JTimeObj();
    ~JTimeObj();
    boolean isTimeChanged();
    virtual void delInput(int n, class JLinkObj& link);
    virtual void delAllInput(int n=-1);
    void updateTime();
    virtual void run();
    virtual void reset();
    virtual void startup();
    virtual void close();
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
    JDate date, oldd;
    int valid;
    JThread thread;
};

#endif
