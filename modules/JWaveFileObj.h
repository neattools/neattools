#if !defined( _JWaveFileObj_h )
#define _JWaveFileObj_h

#include "JRecorderObj.h"

class JWaveFileObj : public JRecorderObj {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JWaveFileObj();
    ~JWaveFileObj();
    virtual void record();
    virtual void play();
    virtual void close();
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JFRect inputArea(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void engine(int n, JLinkObj& link);
    virtual void run();
    virtual boolean check(boolean redraw);
    virtual boolean writeHeader(int _id);
  protected:
    int id;
    int blockSize;
    int nBlockAlign;
    JBlock data;
};

#endif
