#if !defined( _JView_h )
#define _JView_h

#include "JRuler.h"
#include "JScroller.h"
#include "JLabel.h"
#include "JViewSet.h"
#include "JLinkObj.h"
#include "JFocusSet.h"
#include "JFile.h"
#include "JModuleObj.h"
#include "JThread.h"
#include "JCriticalSection.h"

class JView : public JCanvas {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
    boolean checkSave();
    boolean checkSelected();
    boolean CM_SelectAll();
    boolean CM_Cut();
    boolean CM_Copy();
    boolean CM_Paste();
    boolean CM_Delete();
    boolean CM_ToFront();
    boolean CM_ToBack();
    boolean CM_NewFile();
    boolean CM_OpenFile();
    boolean CM_OpenFile(JString fname);
    boolean CM_SaveFile();
    boolean CM_SaveAs();
    boolean CM_Import();
    boolean CM_Export();
    boolean CM_Group();
    boolean CM_Ungroup();
    boolean CM_Cancel();
    boolean CM_LoadModule(JString name="");
    boolean CM_TopMost(boolean mode);
    boolean CM_UserMode(boolean mode);
    boolean CM_Caption(boolean mode);
    boolean CM_EditEnabled(boolean mode);
    boolean CM_GuideVisible(boolean mode);
    boolean CM_LinkVisible(boolean mode);
    boolean CM_HiddenVisible(boolean mode);
    boolean CM_RulerVisible(boolean mode);
    boolean CM_ScalerVisible(boolean mode);
    boolean CM_GridVisible(boolean mode);
  public:
    enum { NTL_MODE, MOD_MODE, CFG_MODE};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JView* create(JComponent *p);
    JView();
    JView(const JView& obj);
    virtual void startup();
    virtual void destroy();
    virtual void activate();
    virtual void deactivate();
    virtual void idleAction(int id);
    virtual void layout();
    virtual void layoutMinimized();
    virtual void layoutRestored();
    virtual void paint(JGraphics g);
    virtual boolean needRedraw();
    virtual boolean handleJEvent(JEvent& e);
    virtual boolean mouseDown(JEvent& e, int x, int y);
    virtual boolean mouseMove(JEvent& e, int x, int y);
    virtual boolean mouseDrag(JEvent& e, int x, int y);
    virtual boolean mouseEnter(JEvent& e, int x, int y);
    virtual boolean mouseExit(JEvent& e, int x, int y);
    virtual boolean mouseUp(JEvent& e, int x, int y);
    virtual boolean keyDown(JEvent& e, int key);
    virtual boolean action(JEvent& e, JObject* arg);
    virtual boolean childNotify(JEvent& e, JObject* arg);
    virtual boolean peerNotify(JEvent& e, JObject* arg);
    virtual boolean closeQuery(JEvent& e);
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
    virtual boolean propertyDialog(int x, int y);
    double getScale();
    boolean setScale(double _scale, boolean frepaint);
    boolean setView(JFPoint fpt, boolean frepaint);
    boolean setXYValue(double _x, double _y);
    boolean writeFile(JString name, boolean _importMode = NTL_MODE);
    boolean readFile(JString name);
    void putFileName(JString name);
    JCanvas *tool, *sPanel, *tPanel, *workArea;
    JRuler *vRuler, *hRuler, *stub;
    JScroller *vScroller, *hScroller, *sScroller;
    JLabel *xValue, *yValue, *dValue;
    JLabel *zValue, *sValue;
    JComponent *vSep, *hSep;
    JComponent *group, *ungroup, *loadModule;
    JComponent *noZoom, *about, *exit;
    JComponent *zoomIn2, *zoomIn;
    JComponent *zoomOut, *zoomOut2;
    JComponent *cut, *copy, *paste, *toFront, *toBack;
    JComponent *newFile, *openFile, *saveFile, *saveAs;
    JComponent *importb, *exportb;
    JCanvas *edit, *guide, *link;
    JCanvas *dash, *ruler, *viewer;
    JCanvas *scaler, *grid;
  protected:
    boolean topMost;
    boolean userMode;
    boolean withCaption;
    boolean cursorVisible;
    boolean importMode;
    boolean dragVisible, dragEnabled, areaVisible;
    boolean canConnect;
    JFile configure;
    JCriticalSection critical, waiting, process;
    boolean mousePressed;
    boolean focusOn;
    JRegion region;
    int dpi, zoom, guideStyle;
    int ixmin, ixmax, iymin, iymax;
    int icx, icy, ibx, iby;
    double xmin, xmax, ymin, ymax;
    double cx, cy, bx, by, delta;
    double scale, dscale, rscale;
    int updateLock, area;
    int currentGroup, destGroup;
    int guideSnapDist;
    int maxRecentFiles;
    JModuleObj *currentObj, *destObj, *currentEdit;
    JViewObj *currentHit;
    JLinkObj *currentLink, destLink;
    JViewSet viewSet, frameSet, linkSet;
    JViewSet vGuideSet, hGuideSet;
    JViewSet dragSet, areaSet;
    JFocusSet focusSet, focusGuides;
    JColor backgroundColor, gridColor;
    JColor guideColor, linkColor, frameColor;
    JString fileName, executeFile, userModePassword;
    JHashTable waitingHash;
    JArray recentFiles, waitingArray, processArray;
    static int hashSize;
    static int nModuleBox;
    static char* mbTag[];
    static char* mbTitle[];
    static JRect mbDefault;
    static JRect mbExt[];
    static JCanvas *mbBtn[];
    static JComponent *mBox[];
    static int nToolBox;
    static JCanvas *tbPanel[];
    static JCanvas *tbCanvas[];
    static char* tbTag[];
    static char* tbTitle[];
    static JRect tbDefault;
    static JRect tbExt[];
    static JCanvas *tbBtn[];
    static JComponent *tBox[];
    static JArray externalModuleTag;
    int FtoI(double v);
    double ItoF(int v);
    virtual void beforePaint(JRect *rect = null);
    virtual void afterPaint(JRect *rect = null);
    virtual void showCursor(JRect *rect);
    virtual void showDrag(JRect *rect);
    virtual void showArea(JRect *rect);
    virtual void showMouseDrag(JEvent& e, int x, int y, boolean state);
    void checkValue(int& x, int& y);
    JRect getIExtent(JFRect ext);
    JFRect getFExtent(JRect ext);
    JRect getSnapJRect(int x, int y);
    JFRect getSnapJFRect(double x, double y);
    JRect getApertureJRect(int n, JRect& iext);
    int getApertureNo(JPoint& pt, JRect& iext);
    boolean snapGuideX(double& x, double& dx);
    boolean snapGuideY(double& y, double& dx);
    boolean snapGuideXY(double& x, double& y, double& dx, double& dy);
    boolean snapGuideX(double& x1, double& x2, double& dx);
    boolean snapGuideY(double& y1, double& y2, double& dy);
    boolean snapGridX(double& x, double& dx);
    boolean snapGridY(double& y, double& dx);
    boolean snapGridXY(double& x, double& y, double& dx, double& dy);
    boolean typeMatch(int type1, int type2);
    void removeLink(JLinkObj* link);
    void loadExternalModules();
    boolean loadExternalModule(JString name);
    void updateRecentFiles(JString name);
    void calculateJRegion();
    void clearProcessArray();
    void clearProcessArrayInFocusSet();
    void createModuleBox(int n);
    void createToolBox(int n);
    void addButtons(JComponent* panel, JArray tag);
    void setCurrentEdit(JModuleObj* newEdit = null);
    JDimension getAdjustment();
};

#endif
