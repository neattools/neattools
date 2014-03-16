#if !defined( _J1DViewerObj_h )
#define _J1DViewerObj_h

#include "J1DMeterObj.h"
#include "JImage.h"

class J1DViewerObj : public J1DMeterObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { LINE, COLORMAP, INTENSITY, 
      BAR, COLORMAPBAR, INTENSITYBAR, ID_LAST};
    enum { INPUT, COLOR, BACKGROUND, SYNC, IN_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    J1DViewerObj(int _type = HORIZONTAL);
    virtual void startup();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual int inputType(int n);
    virtual JString inputTag(int n);
    virtual JFRect outputArea(int n);
    virtual int outputFace(int n);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual double outputPos(int n, JFPoint opt);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean setValue(int _value);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual void addButton(JComponent *panel);
  protected:
    int sequence;
    int oldValue;
    int bufSize;
    int tail, head;
    int headBase, ovBase;
    int *data;
    int id;
    JBlock buf;
    void initialize();
    void drawFrame(JGraphics g, JRect rect);
    void drawLine(JGraphics g, JRect rect, int& head, int& sequence, int& oldValue);
};

#endif
