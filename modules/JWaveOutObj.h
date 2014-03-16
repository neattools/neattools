#if !defined( _JWaveOutObj_h )
#define _JWaveOutObj_h

#include "JAddObj.h"
#include "JThread.h"
#include "JCriticalSection.h"

class JWaveOutObj : public JAddObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { NORMAL, PAUSE, OVERFLOW};
    enum { OUT_COUNTER, OUT_DELTA, OUT_FEEDBACK, OUT_LAST};
    enum { NORM_BLOCK, HEAD_BLOCK, TAIL_BLOCK};
    enum { _1M08, _1S08, _1M16, _1S16, _2M08, _2S08,
      _2M16, _2S16, _4M08, _4S08, _4M16, _4S16, 
      _8M08, _8S08, _8M16, _8S16, _LAST};
    static int msPerBlock;
    static char* formatTag[];
    static int frequencyValue[];
    static int channelValue[];
    static int bitsValue[];
    static int formatValue[];
    static int getNumDevs();
    virtual const char* className() const;
    virtual JObject* clone() const;
    JWaveOutObj();
    JWaveOutObj(int _wid, int _fid = 0);
    virtual ~JWaveOutObj();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual int inputType(int n);
    virtual boolean inputAllowed(int n);
    virtual JString outputTag(int n);
    virtual JFRect outputArea(int n);
    virtual int outputFace(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void reset();
    virtual void close();
    virtual void open();
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getDeviceTag();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean dataNotify(JEvent& e, void* data);
    virtual boolean check();
    virtual void addButton(JComponent *panel);
  protected:
    int id, wid, fid;
    int handle;
    int blockSize;
    int bufferSize;
    int current, top, delta, feedback;
    int enabled;
    boolean pause;
    boolean valid;
    boolean connected;
    JString name;
    JArray block;
    JCriticalSection cs;
};

#endif
