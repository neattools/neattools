#if !defined( _JLabelObj_h )
#define _JLabelObj_h

#include "JLEDObj.h"

class JLabelObj : public JLEDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { HALIGN_AUTO, HALIGN_FRACTION};
    enum { IN_DATA, IN_COLOR, IN_BKGND, IN_EDITFOCUS, IN_CLEAR, IN_IMAGEFILE, IN_LAST};
    enum { OUT_DATA, OUT_NEXTFOCUS, OUT_ENTER, OUT_ESCAPE, OUT_LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void calculateJRegion(JRegion& rgn, double dx, double dy, double scale);
    JLabelObj();
    virtual void startup();
    virtual void reset();
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void update(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual void engine(int n, JLinkObj& link);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean mouseDown(JEvent& e, double x, double y);
    virtual boolean mouseDrag(JEvent& e, double x, double y);
    virtual boolean mouseUp(JEvent& e, double x, double y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean gotFocus(JEvent& e);
    virtual boolean lostFocus(JEvent& e);
    virtual boolean gotEditFocus(JEvent& e);
    virtual boolean lostEditFocus(JEvent& e);
    virtual boolean setLabel(JString _label);
  protected:
    JString label, imageFile, type;
    int cursor, mBegin, mEnd;
    int fraction;
    int fontId;
    boolean fontStyleId;
    boolean hasEditFocus;
    boolean canEdit;
    boolean focusOn;
    boolean raise;
    boolean align;
    boolean hAlign;
    boolean echoOn;
    boolean needRelocate;
    boolean dirty;
    boolean mousePressed;
    boolean drawBorder;
    boolean drawBackground;
    boolean useImage;
    boolean autoScaleImage;
    static boolean overwriteOn;
    int nextFocus, enterPressed, escapePressed;
    double xpos;
    virtual JString getEditSet();
    virtual void processCtrlKeys(int key);
    boolean fillImage(JGraphics g, JRect rect);
};

#endif
