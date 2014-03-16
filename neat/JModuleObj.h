#if !defined( _JModuleObj_h )
#define _JModuleObj_h

#include "JViewObj.h"
#include "JArray.h"
#include "JBlock.h"
#include "JColor.h"
#include "JFocusSet.h"
#include "JDataType.h"

class
#include "JNEAT.hpp"
JModuleObj : public JViewObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { LEFT, TOP, RIGHT, BOTTOM};
    enum { DIRECT_MODE, REPAINT_MODE, REGION_MODE, REQUEST_MODE,
      EXTENT_MODE, JPOINT_MODE, EXECUTE_MODE};
    static int limit;
    static int depth;
    static int depth2;
    virtual const char* className() const;
    virtual JObject* clone() const;
    JModuleObj();
    void addEvent(int mask);
    void removeEvent(int mask);
    virtual int getEventMask();
    virtual JRegion getJRegion();
    virtual JRect getIExtent(double dx, double dy, double scale);
    int inputGroupMax();
    int outputGroupMax();
    JFocusSet& inputSet(int n);
    JFocusSet& outputSet(int n);
    JString inputTagType(int n);
    JString outputTagType(int n);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual void remove();
    virtual JFRect calculateUpdate();
    virtual JFRect calculateInputUpdate(int n=-1);
    virtual JFRect calculateOutputUpdate(int n=-1);
    virtual void calculateJRegion(JRegion& rgn, double dx, double dy, double scale);
    virtual JViewObj* duplicate(class JViewSet* _parent = null, JDictionary* dict = null);
    virtual int inputType(int n);
    virtual int outputType(int n);
    virtual boolean cond(int n, class JLinkObj& link);
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual void access(int n, class JLinkObj& link, const JDataType& data);
    virtual boolean inputAllowed(int n);
    virtual boolean outputAllowed(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputAreaNo(JFPoint fpt);
    virtual int outputAreaNo(JFPoint fpt);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, class JLinkObj& link);
    virtual JFPoint outputPoint(int n, class JLinkObj& link);
    virtual double outputPos(int n, JFPoint opt);
    virtual void engine(int n, JLinkObj& link);
    virtual boolean isBroadcasting();
    virtual void broadcast(int n);
    virtual void condBroadcast(int n);
    virtual void addInput(int n, class JLinkObj& link);
    virtual void delInput(int n, class JLinkObj& link);
    virtual void delAllInput(int n=-1);
    virtual void addOutput(int n, class JLinkObj& link);
    virtual void delOutput(int n, class JLinkObj& link);
    virtual void delAllOutput(int n=-1);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean propertyDialog(int x, int y);
    virtual void addButton(JComponent *panel);
    virtual void addLinks(JViewSet& set, JHashTable& hash);
    virtual void addConnectedModules(JViewSet& set, JHashTable& hash);
    virtual boolean isOpaque();
    virtual boolean gotEditFocus(JEvent& e);
    virtual boolean lostEditFocus(JEvent& e);
    boolean requestEditFocus();
    void addModuleButton(JComponent *panel, const JModuleObj& obj);
    void repaint();
    void repaint(int x, int y, int w, int h);
    void repaintView(JFRect rect, int mode = REPAINT_MODE);
    JRect queryExtent();
    JPoint queryJPoint(double x, double y);
    JColor getModuleColor();
  protected:
    int igm, ogm, igSize, ogSize;
    int eventMask;
    JColor moduleColor;
    JArray inputGroup;
    JArray outputGroup;
    JRegion region;
    void drawText(JGraphics g, JString text, JRect rect);
    JFPoint topPoint(int n, class JLinkObj& link, int start, int N, 
      double from = 0.25, double delta = 0.5);
    JFPoint bottomPoint(int n, class JLinkObj& link, int start, int N, 
      double from = 0.25, double delta = 0.5);
    JFPoint leftPoint(int n, class JLinkObj& link, int start, int N, 
      double from = 0.25, double delta = 0.5);
    JFPoint rightPoint(int n, class JLinkObj& link, int start, int N, 
      double from = 0.25, double delta = 0.5);
    JFRect topArea(int n, int start, int N, 
      double from = 0.25, double delta = 0.5, int factor = 6);
    JFRect bottomArea(int n, int start, int N, 
      double from = 0.25, double delta = 0.5, int factor = 6);
    JFRect leftArea(int n, int start, int N, 
      double from = 0.25, double delta = 0.5, int factor = 6);
    JFRect rightArea(int n, int start, int N, 
      double from = 0.25, double delta = 0.5, int factor = 6);
};

#endif
