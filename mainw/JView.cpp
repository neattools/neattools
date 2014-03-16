/*

  The following module use Thread.
  Test carefully.
  PS. Must have reset to avoid double close!
  PS. Must not use thread.waitFor() to close it will cause dead lock!
  if have input must use CriticalSection

  JCOMObj.cpp, JTimeObj.cpp,
  JTimerObj.cpp, JSocketObj.cpp
  JRecorderObj.cpp, JWaveFileObj.cpp

  The following module use File Handle.
  Test carefully.
  PS. Mush have reset to avoid double close!

  JMIDIOutObj.cpp
  JWaveOutObj.cpp, JWaveInObj.cpp

  If use array or list in module, you should
  Dereference it in startup()

*/

#include "JView.h"
#include "JMath.h"
#include "JAbout.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JBlockInputStream.h"
#include "JBlockOutputStream.h"
#include "JBufferedInputStream.h"
#include "JBufferedOutputStream.h"
#include "JIOException.h"
#include "JClassReferenceException.h"
#include "JIllegalArgumentException.h"
#include "JToggleButton.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JLinkObj.h"
#include "JGuideObj.h"
#include "JBorderLayout.h"
#include "JGridLayout.h"
#include "JFlowLayout.h"
#include "JPushButton.h"
#include "JSeparator.h"
#include "JModuleButton.h"
#include "JMixerObj.h"
#include "JFileBox.h"
#include "JMessageBox.h"
#include "JClipboard.h"
#include "JPObject.h"
#include "JFile.h"
#include "JScrambledStringProperty.h"

#define ZOOM_MAX 50
#define ZOOM_MIN -30
#define ZOOM_STEP 0.1
#define adjust(v,vmin,vmax) (min(vmax, max(vmin, v)))
#define EXT1 "*.ntl"
#define EXT2 "*.mod"
#define EXT3 "*.dll"

char* theJView = JView().Register();

double ztos(int &zoom) {
  if (zoom > ZOOM_MAX) zoom = ZOOM_MAX;
  if (zoom < ZOOM_MIN) zoom = ZOOM_MIN;
  return JMath::pow(2.0, ZOOM_STEP*zoom);
}

int stoz(double scale) 
{ return JMath::round(JMath::log(scale)/JMath::log(2.0)/ZOOM_STEP);}

enum { NOWHERE = -1, LT_BOX, RT_BOX, RB_BOX, LB_BOX,
  TOP_BOX, RIGHT_BOX, BOTTOM_BOX, LEFT_BOX, PROP_BOX, MAX_BOX, 
  HIT, MOVE, SELECT, DRAG,
  VGUIDE, HGUIDE, CORNER,
  MOVE_VGUIDE, MOVE_HGUIDE, MOVE_GUIDES,
  DRAG_INPUT, DRAG_OUTPUT, DRAG_MODULE, 
  REMOVE_LINK, ADJUST_FROM, ADJUST_TO,
  OCCUPIED_INPUT, OCCUPIED_OUTPUT };
enum { BEFORE, CURRENT, AFTER};

JRect JView::getApertureJRect(int n, JRect& iext) {
  int cursorSize = guideSnapDist*2+1;
  switch (n) {
    case PROP_BOX:
      return JRect(
        iext.x+iext.width-cursorSize, 
        iext.y+iext.height-cursorSize,
        cursorSize, cursorSize);
    case LT_BOX:
      return JRect(iext.x-cursorSize-1,
        iext.y-cursorSize-1,
        cursorSize, cursorSize);
    case RT_BOX:
      return JRect(iext.x+iext.width+1,
        iext.y-cursorSize-1,
        cursorSize, cursorSize);
    case RB_BOX:
      return JRect(iext.x+iext.width+1,
        iext.y+iext.height+1,
        cursorSize, cursorSize);
    case LB_BOX:
      return JRect(iext.x-cursorSize-1,
        iext.y+iext.height+1,
        cursorSize, cursorSize);
    case TOP_BOX:
      return JRect(iext.x+(iext.width-cursorSize)/2,
        iext.y-cursorSize-1,
        cursorSize, cursorSize);
    case RIGHT_BOX:
      return JRect(iext.x+iext.width+1,
        iext.y+(iext.height-cursorSize)/2,
        cursorSize, cursorSize);
    case BOTTOM_BOX:
      return JRect(iext.x+(iext.width-cursorSize)/2,
        iext.y+iext.height+1,
        cursorSize, cursorSize);
    case LEFT_BOX:
      return JRect(iext.x-cursorSize-1,
        iext.y+(iext.height-cursorSize)/2,
        cursorSize, cursorSize);
  }
  return JRect();
}

int JView::getApertureNo(JPoint& pt, JRect& iext) {
  for (int i=0; i<MAX_BOX; i++) {
    if (getApertureJRect(i, iext).inside(pt.x, pt.y)) 
      return i;
  }
  return NOWHERE;
}

JString toJString(double x, double y,
  double width, double height) {
  return JString("(")+
    JDouble::toJStringF(x)+","+
    JDouble::toJStringF(y)+")-("+
    JDouble::toJStringF(width)+"x"+
    JDouble::toJStringF(height)+")";
}

void JView::checkValue(int& x, int& y) {
  double nx = adjust(ItoF(x+ibx), xmin, xmax);
  double ny = adjust(ItoF(y+iby), ymin, ymax);
  x = FtoI(nx)-ibx;
  y = FtoI(ny)-iby;
}

JView* JView::create(JComponent *p) 
{ return (JView*)createJComponent(theJView, p);}

const char* JView::className() const { return "JView";}

JObject* JView::clone() const { return new JView(*this);}

JView::JView() : waitingHash(hashSize) {
  mousePressed = false;
  state = CONVEX;
  base = ratio = 0;
  vRuler = hRuler = stub = null;
  vScroller = hScroller = null;
  xValue = yValue = dValue = sValue = zValue = null;
  dpi = 64;
  zoom = 0;
  guideStyle = 0;
  xmin = ymin = 0.0;
  xmax = 11.0;
  ymax = 8.5;
  scale = 0.0;
  bx = by = cx = cy = 0.0;
  updateLock = 0;
  guideSnapDist = 4;
  maxRecentFiles = 8;
  area = -1;
  importMode = NTL_MODE;
  cursorVisible = false;
  dragEnabled = false;
  dragVisible = false;
  areaVisible = false;
  focusOn = false;
  userMode = false;
  withCaption = true;
  topMost = false;
  currentObj = null;
  currentHit = null;
  currentLink = null;
  currentEdit = null;
  backgroundColor = JColor::lightGray;
  gridColor = JColor::blue.darker();
  frameSet.addRect(xmin, ymin, xmax-xmin, ymax-ymin);
  frameSet.calculateExtent();
}

/* Needed by GCC */
JView::JView(const JView& obj) { *this = obj;}

void DoToFocus(const JObject* obj, void** arg) 
{ ((JFocusSet*)arg)->add(*(JViewObj*)obj);}

void DoCheckLink(const JObject* obj, void** arg) { 
  JLinkObj *link = (JLinkObj*)obj;
  JHashTable &hash = *(JHashTable*)arg[0];
  if (hash[JPObject(link->from)] && 
    hash[JPObject(link->to)]) 
    ((JFocusSet*)arg[1])->add(*(JViewObj*)obj);
}

void JView::writeContent(JOutputStream& os) {
  critical.lock();
  putInteger(os, "importMode", importMode);
  if (importMode == MOD_MODE) {
    JFocusSet linkSelected;
    JHashTable hash(hashSize);
    void* arg[] = { &hash, &linkSelected};
    putDouble(os, "bx", bx);
    putDouble(os, "by", by);
    putDouble(os, "scale", scale);
    focusSet.toHash(hash);
    linkSet.forEachChild(DoCheckLink, arg);
    putObject(os, "focusSet", focusSet);
    putObject(os, "linkSelected", linkSelected);
  } else {
    putDouble(os, "cx", cx);
    putDouble(os, "cy", cy);
    putDouble(os, "bx", bx);
    putDouble(os, "by", by);
    putDouble(os, "xmin", xmin);
    putDouble(os, "ymin", ymin);
    putDouble(os, "xmax", xmax);
    putDouble(os, "ymax", ymax);
    putDouble(os, "scale", scale);
    putInteger(os, "zoom", zoom);
    putInteger(os, "dpi", dpi);
    putInteger(os, "guideVisible", guide->getBState());
    putInteger(os, "editEnabled", edit->getBState());
    putInteger(os, "linkVisible", link->getBState());
    putInteger(os, "dashVisible", dash->getBState());
    putInteger(os, "rulerVisible", ruler->getBState());
    putInteger(os, "scalerVisible", scaler->getBState());
    putInteger(os, "gridVisible", grid->getBState());
    putInteger(os, "userMode", userMode);
    putInteger(os, "maximized", theMainWindow->getMaximized());
    putInteger(os, "topMostWindow", topMost);
    putString(os, "userModePassword", 
      JScrambledStringProperty::scramble(userModePassword));
    if (importMode == NTL_MODE) {
      JRect mainWindow = (JRect)*theMainWindow;
      putInteger(os, "withCaption", withCaption);
      putObject(os, "mainWindow", mainWindow);
      sValue->setScaleTotal(4);
      putObject(os, "vGuideSet", vGuideSet);
      sValue->setScale(1);
      putObject(os, "hGuideSet", hGuideSet);
      sValue->setScale(2);
      putObject(os, "viewSet", viewSet);
      sValue->setScale(3);
      putObject(os, "linkSet", linkSet);
      sValue->setScale(4);
    } else {
      putObject(os, "fileName", fileName);
      putObject(os, "guideColor", guideColor);
      putInteger(os, "guideStyle", guideStyle);
      putInteger(os, "guideSnapDist", guideSnapDist);
      putInteger(os, "maxRecentFiles", maxRecentFiles);
      putObject(os, "linkColor", linkColor);
      putObject(os, "frameColor", frameColor);
      putObject(os, "backgroundColor", backgroundColor);
      putObject(os, "gridColor", gridColor);
      putObject(os, "recentFiles", recentFiles);
      int i;
      for (i=0; i<nToolBox; i++) {
        putInteger(os, JString("tbFloating")+
          JInteger::toJString(i), tbBtn[i]->getBState());
        if (tBox[i]) tbExt[i] = *tBox[i];
        putObject(os, JString("tbExt")+
          JInteger::toJString(i), tbExt[i]);
      }
      for (i=0; i<nModuleBox; i++) {
        putInteger(os, JString("mbVisible")+
          JInteger::toJString(i), mbBtn[i]->getBState());
        if (mBox[i]) mbExt[i] = *mBox[i];
        putObject(os, JString("mbExt")+
          JInteger::toJString(i), mbExt[i]);
      }
    }
  }
  critical.unlock();
}

void JView::readContent(JDictionary& dict) {
  JObject *obj;
  JDictionary table(hashSize);
  importMode = (boolean)getInteger(dict, "importMode");
  if (importMode == MOD_MODE) {
    JFocusSet *import;
    JFocusSet *linkSelected;
    obj = getObject(dict, "focusSet");
    if (obj) import = (JFocusSet*)obj;
    obj = getObject(dict, "linkSelected");
    if (obj) linkSelected = (JFocusSet*)obj;
    import->root = this;
    import->fixParent();
    linkSelected->fixParent();
    import->calculateExtent();
    double dx, dy;
    double obx = getDouble(dict, "bx");
    double oby = getDouble(dict, "by");
    double oscale = getDouble(dict, "scale");
    double kscale = oscale/scale;
    if (kscale <= 0.0) kscale = 1.0;
    dx = (bx-import->x)+(import->x-obx)*kscale;
    dy = (by-import->y)+(import->y-oby)*kscale;
    JFRect info(import->x, import->y, dx, dy);
    import->rescale(info, kscale, kscale);
    import->fixPointer(table);
    linkSelected->fixPointer(table);
    beforePaint();
    areaSet.delAll();
    dragSet.delAll();
    focusSet.delAll();
    import->forEachChild(DoToFocus, (void**)&focusSet);
    import->reparent(viewSet);
    linkSelected->reparent(linkSet);
    viewSet.calculateExtent();
    linkSet.calculateExtent();
    focusSet.calculateExtent();
    calculateJRegion();
    focusSet.startup();
    repaint(getIExtent(focusSet.calculateUpdate()));
    afterPaint();
  } else {
    double nscale;
    setCurrentEdit();
    viewSet.close();
    beforePaint();
    JThread::sleep(100); // Wait for thread to exit
    clearProcessArray();
    areaSet.delAll();
    dragSet.delAll();
    cx = getDouble(dict, "cx");
    cy = getDouble(dict, "cy");
    bx = getDouble(dict, "bx");
    by = getDouble(dict, "by");
    xmin = getDouble(dict, "xmin");
    ymin = getDouble(dict, "ymin");
    xmax = getDouble(dict, "xmax");
    ymax = getDouble(dict, "ymax");
    nscale = getDouble(dict, "scale");
    zoom = getInteger(dict, "zoom");
    dpi = getInteger(dict, "dpi");
    guide->setBState(getInteger(dict, "guideVisible"));
    edit->setBState(getInteger(dict, "editEnabled"));
    link->setBState(getInteger(dict, "linkVisible"));
    dash->setBState(getInteger(dict, "dashVisible"));
    ruler->setBState(getInteger(dict, "rulerVisible"));
    scaler->setBState(getInteger(dict, "scalerVisible"));
    grid->setBState(getInteger(dict, "gridVisible"));
    userMode = (boolean)getInteger(dict, "userMode", 0);
    topMost = (boolean)getInteger(dict, "topMostWindow", 0);
  boolean maximized = (boolean)getInteger(dict, "maximized", 0);
    userModePassword = JScrambledStringProperty::unscramble(getString(dict, "userModePassword"));
    scale = 0;
    setScale(nscale, false);
    CM_TopMost(topMost);
    if (importMode == NTL_MODE) {
      withCaption = (boolean)getInteger(dict, "withCaption", 1);
      sValue->setScaleTotal(9);
      viewSet.delAll();
      linkSet.delAll();
      vGuideSet.delAll();
      hGuideSet.delAll();
      focusSet.delAll();
      sValue->setScale(1);
      obj = getObject(dict, "vGuideSet");
      if (obj) vGuideSet = *(JFocusSet*)obj;
      sValue->setScale(2);
      obj = getObject(dict, "hGuideSet");
      if (obj) hGuideSet = *(JFocusSet*)obj;
      sValue->setScale(3);
      obj = getObject(dict, "viewSet");
      if (obj) viewSet = *(JViewSet*)obj;
      sValue->setScale(4);
      obj = getObject(dict, "linkSet");
      if (obj) linkSet = *(JViewSet*)obj;
      sValue->setScale(5);
      viewSet.root = this;
      vGuideSet.fixParent();
      hGuideSet.fixParent();
      viewSet.fixParent();
      linkSet.fixParent();
      sValue->setScale(6);
      viewSet.fixPointer(table);
      sValue->setScale(7);
      linkSet.fixPointer(table);
      sValue->setScale(8);
      viewSet.calculateExtent();
      linkSet.calculateExtent();
      calculateJRegion();
      viewSet.startup();
      sValue->setScale(9);
      layoutRestored();
    } else {
      obj = getObject(dict, "fileName");
      if (obj) fileName = *(JString*)obj;
      obj = getObject(dict, "guideColor");
      if (obj) guideColor = *(JColor*)obj;
      obj = getObject(dict, "linkColor");
      if (obj) linkColor = *(JColor*)obj;
      obj = getObject(dict, "frameColor");
      if (obj) frameColor = *(JColor*)obj;
      obj = getObject(dict, "backgroundColor");
      if (obj) backgroundColor = *(JColor*)obj;
      obj = getObject(dict, "gridColor");
      if (obj) gridColor = *(JColor*)obj;
      obj = getObject(dict, "recentFiles");
      if (obj) recentFiles = *(JArray*)obj;
      guideStyle = getInteger(dict, "guideStyle");
      guideSnapDist = getInteger(dict, "guideSnapDist");
      guideSnapDist = max(3, min(8, guideSnapDist));
      maxRecentFiles = getInteger(dict, "maxRecentFiles");
      maxRecentFiles = max(4, min(20, maxRecentFiles));
      int i;
      for (i=0; i<nToolBox; i++) {
        tbBtn[i]->setBState(getInteger(dict, 
          JString("tbFloating")+
          JInteger::toJString(i)));
        obj = getObject(dict, JString("tbExt")+
          JInteger::toJString(i));
        if (obj) tbExt[i] = *(JRect*)obj;
	if (!obj || !(tbExt[i] && *theRootWindow)) 
	  tbExt[i] = tbDefault;
        createToolBox(i);
      }
      for (i=0; i<nModuleBox; i++) {
        mbBtn[i]->setBState(getInteger(dict, 
          JString("mbVisible")+
          JInteger::toJString(i)));
        obj = getObject(dict, JString("mbExt")+
          JInteger::toJString(i));
        if (obj) mbExt[i] = *(JRect*)obj;
	if (!obj || !(mbExt[i] && *theRootWindow)) 
	  mbExt[i] = mbDefault;
	createModuleBox(i);
      }
    }
    setXYValue(cx, cy);
    afterPaint();

    vRuler->show(ruler->getBState() && !userMode);
    hRuler->show(ruler->getBState() && !userMode);
    sScroller->show(scaler->getBState() && !userMode);
    stub->show(ruler->getBState() && !userMode);
    sScroller->show(scaler->getBState() && !userMode);
    vScroller->show(!userMode);
    hScroller->show(!userMode);
    sPanel->show(!userMode);
    tPanel->show(!userMode);
    theMainWindow->setResizable(!userMode);
    theMainWindow->setCaption(withCaption);
    obj = getObject(dict, "mainWindow");
    if (obj) theMainWindow->reshape(*(JRect*)obj);
    if (maximized) theMainWindow->setMaximized();
    theMainWindow->layout();
    repaint();
  }
}

boolean JView::checkSave() {
  int result;
RETRY:
  if (fileName.length()) {
    result = JMessageBox::create(
      JString("Save file ")+fileName+
      " first ?", JMessageBox::BTN_YESNOCANCEL);
  } else {
    result = JMessageBox::create(
      "Save untitled file first ?", 
      JMessageBox::BTN_YESNOCANCEL);
  }
  if (result == JMessageBox::CANCEL) return false;
  if (result == JMessageBox::YES) {
    if (fileName.length()) {
      if (!writeFile(fileName)) {
        JMessageBox::create("File write error !", 
        JMessageBox::BTN_OK);
        return false;
      }
    } else if (!CM_SaveAs()) goto RETRY;
  }
  return true;
}

boolean JView::checkSelected() {
  if (focusSet.isEmpty()) {
    JMessageBox::create("Please select objects first.", 
      JMessageBox::BTN_OK);
    return false;
  }
  return true;
}

void DoSelectAll(const JObject* obj, void** arg)
{ ((JFocusSet*)arg)->add(*(JViewObj*)obj);}

boolean JView::CM_SelectAll() {
  beforePaint();
  focusSet.delAll();
  viewSet.forEachChild(DoSelectAll, (void**)&focusSet);
  focusSet.calculateExtent();
  afterPaint();
  return true;
}

boolean JView::CM_Cut() {
  if (!checkSelected()) return false;
  return CM_Copy() && CM_Delete();
}

boolean JView::CM_Copy() {
  if (!checkSelected()) return false;
  JBlock data;
  JBlockOutputStream bos(data);
  importMode = MOD_MODE;
  write(bos);
  bos.close();
  JClipboard cb;
  cb.open(handle);
  cb.empty();
  cb.setData(0, data);
  cb.close();
  return true;
}

boolean JView::CM_Paste() {
  JClipboard cb;
  if (cb.isAvailable(0)) {
    JBlock data;
    JBlockInputStream bis(data);
    cb.open(handle);
    data = cb.getData(0);
    cb.close();
    if (data.size()) {
      read(bis);
      return true;
    }
  }
  JMessageBox::create("Clipboard data is not available.", 
    JMessageBox::BTN_OK);
  return false;
}

void DoAddConnectedModules(const JObject* obj, void** arg) {
  ((JModuleObj*)obj)->addConnectedModules(
    *(JViewSet*)arg[0],
    *(JHashTable*)arg[1]);
}

boolean JView::CM_Delete() {
  if (!checkSelected()) return false;
  JFocusSet connected;
  JHashTable hash(hashSize);
  void* arg[] = { &connected, &hash};
  JRect rect = getIExtent(focusSet.calculateUpdate());
  focusSet.toHash(hash);
  if (currentEdit && hash[JPObject(currentEdit)])
    setCurrentEdit();
  focusSet.close();
  focusSet.forEachNode(DoAddConnectedModules, arg);
  rect |= getIExtent(connected.calculateUpdate());
  beforePaint();
  JThread::sleep(100); // wait for threads to exit
  clearProcessArrayInFocusSet();
  areaSet.delAll();
  dragSet.delAll();
  focusSet.remove();
  focusSet.calculateExtent();
  viewSet.calculateExtent();
  calculateJRegion();
  rect |= getIExtent(connected.calculateUpdate());
  repaint(rect);
  afterPaint();
  area = NOWHERE;
  currentHit = null;
  currentObj = null;
  sValue->setText(EMPTY);
  return true;
}

boolean JView::CM_ToFront() {
  if (!checkSelected()) return false;
  beforePaint();
  focusSet.toFront();
  calculateJRegion();
  repaint(getIExtent(focusSet));
  afterPaint();
  return true;
}

boolean JView::CM_ToBack() {
  if (!checkSelected()) return false;
  beforePaint();
  focusSet.toBack();
  calculateJRegion();
  repaint(getIExtent(focusSet));
  afterPaint();
  return true;
}

boolean JView::CM_NewFile() {
  if (!checkSave()) return false;
  setCurrentEdit();
  viewSet.close();
  beforePaint();
  JThread::sleep(100); // wait for threads to exit
  clearProcessArray();
  areaSet.delAll();
  dragSet.delAll();
  viewSet.delAll();
  linkSet.delAll();
  vGuideSet.delAll();
  hGuideSet.delAll();
  focusSet.delAll();
  areaSet.calculateExtent();
  dragSet.calculateExtent();
  viewSet.calculateExtent();
  linkSet.calculateExtent();
  vGuideSet.calculateExtent();
  hGuideSet.calculateExtent();
  focusSet.calculateExtent();
  calculateJRegion();
  repaint();
  afterPaint();
  putFileName("");
  return true;
}

boolean JView::CM_OpenFile() {
  JString data(fileName);
  do {
    if (JFileBox::create("Open NeatTools file",
      data, EXT1) != JMessageBox::OK) return false;
  } while (!checkSave());
  return CM_OpenFile(data);
}

boolean JView::CM_OpenFile(JString fname) {
  if (!readFile(fname)) {
    JMessageBox::create("File open error !",
    JMessageBox::BTN_OK);
    return false;
  }
  if (importMode == NTL_MODE) putFileName(fname);
  return true;
}

boolean JView::CM_SaveFile() {
  if (!fileName.length())
    return CM_SaveAs();
  if (!writeFile(fileName)) {
    JMessageBox::create("File write error !", 
      JMessageBox::BTN_OK);
    return false;
  }
  return true;
}

boolean JView::CM_SaveAs() {
  JString data(fileName);
  if (JFileBox::create("Save NeatTools file as", 
    data, EXT1) != JMessageBox::OK) return false;
  if (!writeFile(data)) {
    JMessageBox::create("File write error !", 
      JMessageBox::BTN_OK);
    return false;
  }
  putFileName(data);
  return true;
}

boolean JView::CM_Import() {
  static JString data;
  if (JFileBox::create("Import module file",
    data, EXT2) != JMessageBox::OK) return false;
  if (!readFile(data)) {
    JMessageBox::create("File open error !", 
      JMessageBox::BTN_OK);
    return false;
  }
  return true;
}

boolean JView::CM_Export() {
  if (!checkSelected()) return false;
  static JString data;
  if (JFileBox::create("Export module file", 
    data, EXT2) != JMessageBox::OK) return false;
  if (!writeFile(data, MOD_MODE)) {
    JMessageBox::create("File write error !", 
      JMessageBox::BTN_OK);
    return false;
  }
  return true;
}

boolean JView::CM_Group() {
  if (!checkSelected()) return false;
  if (focusSet.size() == 1) {
    JMessageBox::create("Please select more objects.", 
      JMessageBox::BTN_OK);
    return false;
  }
  JViewSet ns;
  JViewSet *vs = (JViewSet*)viewSet.add(ns);
  focusSet.reparent(*vs);
  focusSet.delAll();
  focusSet.add(*vs);
  vs->calculateExtent();
  sValue->setText(focusSet.info());
  return true;
}

boolean JView::CM_Ungroup() {
  if (!checkSelected()) return false;
  JFocusSet newSet;
  focusSet.ungroup(viewSet, newSet);
  newSet.reshape(focusSet);
  focusSet = newSet;
  sValue->setText(focusSet.info());
  return true;
}  

boolean JView::CM_Cancel() {
  if (!mousePressed) return false;
  JEvent e(this, JEvent::MOUSE_DRAG);
  showMouseDrag(e, e.x, e.y, false);
  mousePressed = false;
  area = NOWHERE-1;
  sValue->setText("User Cancel!");
  return true;
}

boolean JView::CM_LoadModule(JString name) {
  static JString data;
  if (name != JString("")) data = name;
  if (JFileBox::create("Load external module file",
    data, EXT3) != JMessageBox::OK) return false;
  if (!loadExternalModule(data)) {
    JMessageBox::create("External module open error !", 
      JMessageBox::BTN_OK);
    return false;
  }
  int n = nModuleBox-1;
  if (mBox[n]) {
    mBox[n]->kill();
    mBox[n] = null;
  }
  if (!userMode) {
    mbBtn[n]->setBState(true);
    createModuleBox(n);
  }
  return true;
}

JDimension JView::getAdjustment() {
  JDimension sz;
  if (!userMode) {
    sz.width = tPanel->preferredSize().width+
      vScroller->preferredSize().width;
    sz.height = sPanel->preferredSize().height+
      hScroller->preferredSize().height;
    if (ruler->getBState()) {
      sz.width += stub->preferredSize().width;
      sz.height += stub->preferredSize().height;
    }
    if (scaler->getBState()) 
      sz.width += sScroller->preferredSize().width;
  }
  return sz;
}

boolean JView::CM_TopMost(boolean mode) {
  topMost = mode;
  if (topMost) theMainWindow->toTopMost();
  else theMainWindow->toNonTopMost();
  return true;
}

boolean JView::CM_UserMode(boolean mode) {
  beforePaint();
  userMode = mode;
  vRuler->show(ruler->getBState() && !userMode);
  hRuler->show(ruler->getBState() && !userMode);
  stub->show(ruler->getBState() && !userMode);
  sScroller->show(scaler->getBState() && !userMode);
  vScroller->show(!userMode);
  hScroller->show(!userMode);
  sPanel->show(!userMode);
  tPanel->show(!userMode);
  JDimension sz = getAdjustment();
  theMainWindow->setResizable(!userMode);
  if (!theMainWindow->getMaximized()) {
    theMainWindow->reshape(
      theMainWindow->x,
      theMainWindow->y,
      width+sz.width, height+sz.height);
  } else theMainWindow->layout();
  areaSet.delAll();
  dragSet.delAll();
  afterPaint();
  layoutRestored();
  theMainWindow->requestFocus();
  repaint();
  return true;
}

boolean JView::CM_Caption(boolean mode) {
  beforePaint();
  withCaption = mode;
  theMainWindow->setCaption(withCaption);
  afterPaint();
  layoutRestored();
  theMainWindow->requestFocus();
  return true;
}

boolean JView::CM_EditEnabled(boolean mode) {
  beforePaint();
  edit->setBState(mode);
  areaSet.delAll();
  dragSet.delAll();
  afterPaint();
  if (mode) sValue->setText("Edit Enabled.");
  else sValue->setText("Edit Disabled.");
  return true;
}

boolean JView::CM_GuideVisible(boolean mode) {
  beforePaint();
  guide->setBState(mode);
  repaint();
  afterPaint();
  if (mode) sValue->setText("Guide Visible.");
  else sValue->setText("Guide Invisible.");
  return true;
}

boolean JView::CM_LinkVisible(boolean mode) {
  beforePaint();
  link->setBState(mode);
  repaint();
  afterPaint();
  if (mode) sValue->setText("Link Visible.");
  else sValue->setText("Link Invisible.");
  return true;
}

boolean JView::CM_HiddenVisible(boolean mode) {
  beforePaint();
  dash->setBState(mode);
  repaint();
  afterPaint();
  if (mode) sValue->setText("Hidden Line Visible.");
  else sValue->setText("Hidden Line Invisible.");
  return true;
}

boolean JView::CM_RulerVisible(boolean mode) {
  ruler->setBState(mode);
  vRuler->show(mode);
  hRuler->show(mode);
  stub->show(mode);
  viewer->layout();
  if (mode) sValue->setText("Ruler Visible.");
  else sValue->setText("Ruler Invisible.");
  return true;
}

boolean JView::CM_ScalerVisible(boolean mode) {
  scaler->setBState(mode);
  sScroller->show(mode);
  workArea->layout();
  if (mode) sValue->setText("Scaler Visible.");
  else sValue->setText("Scaler Invisible.");
  return true;
}

boolean JView::CM_GridVisible(boolean mode) {
  beforePaint();
  grid->setBState(mode);
  repaint();
  afterPaint();
  if (mode) sValue->setText("Grid Visible.");
  else sValue->setText("Grid Invisible.");
  return true;
}

void JView::putFileName(JString name) {
  JString title = theMainWindow->getText();
  int pos = title.indexOf('-');
  JString subtitle = name;
  if (!name.length()) subtitle = "untitled";
  if (pos > -1) {
    title = title(0, pos+2)+subtitle;
  } else title = title+" - "+subtitle;
  theMainWindow->setText(title);
  fileName = name;
}

boolean JView::readFile(JString name) {
RETRY:
  viewSet.root = this;
  try {
    JFileInputStream fis(name);
    JBufferedInputStream bis(fis);
    read(bis);
    if (importMode == NTL_MODE) 
      updateRecentFiles(name);
    return true;
  } catch (JIllegalArgumentException *e) {
    delete e;
  } catch (JClassReferenceException *e) {
    if (CM_LoadModule(JString(e->getMessage())+(EXT3+1)))
      goto RETRY;
    delete e;
  } catch (JIOException *e) {
    delete e;
  }
  return false;
}

boolean JView::writeFile(JString name, boolean _importMode) {
  try {
    JFile dest(name);
    if (dest.exists()) {
      JFile backup(name);
      backup.changeExt(".bak");
      if (backup.exists()) backup.remove();
      dest.renameTo(backup);
    }
    JFileOutputStream fos(name);
    JBufferedOutputStream bos(fos);
    importMode = _importMode;
    write(bos);
    return true;
  } catch (JIOException *e) {
    delete e;
  }
  return false;
}

#if defined(WIN32)
  DllImport extern void RegisterFileType(char* type, char* name);
#endif

DllImport extern JArray *pClassArray;
DllImport extern JDictionary *pClassDict;

boolean JView::loadExternalModule(JString name) {
  JFile file(name);
  if (file.getName()[0] != 'J') return false;
  int osz = pClassArray->size();
  int hLib = loadDynLinkLibrary(name);
  if (hLib) {
    int nsz = pClassArray->size();
    if (nsz != osz) {
      for (int i=osz; i<nsz; i++) {
        externalModuleTag.append(*(JString*)(*pClassArray)[i]);
      }
    } else freeDynLinkLibrary(hLib);
    return true;
  }
  return false;
}

void JView::loadExternalModules() {
  JFile externDll(JFile(*(JString*)theArgString[0]).getParent());
  JArray externDllList = externDll.list(JFile::LA_FILE, EXT3);
  for (int i=0, sz=externDllList.size(); i<sz; i++)
    loadExternalModule(*(JString*)externDllList[i]);
}

void JView::startup() {
#if defined(WIN32)
  RegisterFileType(".ntl", "NeatTools");
#endif
  int i;
  JBorderLayout border;
  JBorderLayout tborder(2, 2);
  JFlowLayout flow(JFlowLayout::JUSTIFY, 2, 2);
  JFlowLayout tflow(JFlowLayout::LEFT, 2, 2);
  JGridLayout hgrid(1, 0, 2, 2);
  JFont font("times", JFont::BOLD, 12);
  JFont sfont("times", JFont::BOLD, 10);
  JFont ffont("helvetica", JFont::BOLD, 9);

  loadExternalModules();
  configure = JFile(*(JString*)theArgString[0]);
  configure.changeExt(".cfg");
  JMixerObj::openDevs(handle);

  workArea = JCanvas::create(theMainWindow);
  JCanvas *status = JCanvas::create(this);
  JCanvas *xStatus = JCanvas::create(this);
  JCanvas *yStatus = JCanvas::create(this);
  JCanvas *dStatus = JCanvas::create(this);
  JCanvas *zStatus = JCanvas::create(this);
  JCanvas *sStatus = JCanvas::create(this);
  JLabel *xTag = JLabel::create(this, "X:");
  JLabel *yTag = JLabel::create(this, "Y:");

  JCanvas *rPanel = JCanvas::create(this);

  viewer = JCanvas::create(theMainWindow);
  sPanel = JCanvas::create(this);
  tPanel = JCanvas::create(this);
  vSep = JSeparator::create(this, JSeparator::VERTICAL);
  hSep = JSeparator::create(this, JSeparator::HORIZONTAL);

  tool = JCanvas::create(this);
  tool->setJInsets(JInsets(0, 2, 2, 2));
  tool->setLayout(hgrid);

  for (i=0; i<nToolBox; i++) {
    tbPanel[i] = JCanvas::create(this);
    tbBtn[i] = JToggleButton::create(this, tbTag[i], CONVEX);
    tbBtn[i]->setForeground(JColor::blue.darker());
    tbPanel[i]->setJFont(sfont);
    tbPanel[i]->setLayout(tflow);
    tbPanel[i]->add(*tbBtn[i]);
    tbPanel[i]->width = tbBtn[i]->preferredSize().width;
    tool->add(*tbPanel[i]);
  }

  tbPanel[0]->add(*(edit = JToggleButton::create(this, "ED", CONCAVE)));
  tbPanel[0]->add(*(guide = JToggleButton::create(this, "GL", CONCAVE)));
  tbPanel[0]->add(*(link = JToggleButton::create(this, "LK", CONCAVE)));
  tbPanel[0]->add(*(dash = JToggleButton::create(this, "HL", CONVEX)));
  tbPanel[0]->add(*(ruler = JToggleButton::create(this, "Ru", CONCAVE)));
  tbPanel[0]->add(*(scaler = JToggleButton::create(this, "Sc", CONCAVE)));
  tbPanel[0]->add(*(grid = JToggleButton::create(this, "GD", CONCAVE)));

  for (i=0; i<nModuleBox; i++) {
    mbBtn[i] = JToggleButton::create(this, 
      mbTag[i], CONVEX);
    tbPanel[0]->add(*mbBtn[i]);
  }

  tbPanel[0]->add(*(zoomOut2 = JPushButton::create(this, "/2")));
  tbPanel[0]->add(*(zoomOut = JPushButton::create(this, "-")));
  tbPanel[0]->add(*(noZoom = JButton::create(this, "1")));
  tbPanel[0]->add(*(zoomIn = JPushButton::create(this, "+")));
  tbPanel[0]->add(*(zoomIn2 = JPushButton::create(this, "x2")));

  tbPanel[1]->add(*(newFile = JButton::create(this, "nF")));
  tbPanel[1]->add(*(openFile = JButton::create(this, "oF")));
  tbPanel[1]->add(*(saveFile = JButton::create(this, "sF")));
  tbPanel[1]->add(*(saveAs = JButton::create(this, "sA")));
  tbPanel[1]->add(*(importb = JButton::create(this, "iP")));
  tbPanel[1]->add(*(exportb = JButton::create(this, "eP")));
  tbPanel[1]->add(*(cut = JButton::create(this, "Ct")));
  tbPanel[1]->add(*(copy = JButton::create(this, "Cp")));
  tbPanel[1]->add(*(paste = JButton::create(this, "Ps")));
  tbPanel[1]->add(*(toFront = JButton::create(this, "F")));
  tbPanel[1]->add(*(toBack = JButton::create(this, "B")));
  tbPanel[1]->add(*(group = JButton::create(this, "G")));
  tbPanel[1]->add(*(ungroup = JButton::create(this, "uG")));
  tbPanel[1]->add(*(loadModule = JButton::create(this, "LM")));
  tbPanel[1]->add(*(about = JButton::create(this, "?")));
  tbPanel[1]->add(*(exit = JButton::create(this, "Ex")));

  vRuler = JRuler::create(this, JRuler::VERTICAL);
  hRuler = JRuler::create(this, JRuler::HORIZONTAL);
  stub = JRuler::create(this, JRuler::CORNER);
  sScroller = JScroller::create(this, JScroller::VERTICAL);
  vScroller = JScroller::create(this, JScroller::VERTICAL);
  hScroller = JScroller::create(this, JScroller::HORIZONTAL);
  sScroller->setValue(zoom, 1, ZOOM_MIN, ZOOM_MAX+1, false);
  xValue = JLabel::create(this, JDouble::toJStringF(cx));
  yValue = JLabel::create(this, JDouble::toJStringF(cy));
  dValue = JLabel::create(this, "*");
  sValue = JLabel::create(this, "");
  zValue = JLabel::create(this, "100%");
  linkColor = JColor::black;
  guideColor = JColor::green.darker().darker();
  frameColor = JColor::blue.darker();

  viewer->setLayout(border);
  viewer->add(JBorderLayout::WEST, *vRuler);
  viewer->add(JBorderLayout::NORTH, *rPanel);
  viewer->add(JBorderLayout::CENTER, *this);
  rPanel->setLayout(border);
  rPanel->add(JBorderLayout::WEST, *stub);
  rPanel->add(JBorderLayout::CENTER, *hRuler);

  xStatus->setState(JCanvas::CONCAVE);
  xStatus->setDepth(1);
  xTag->setBaseRatio(2, 2);
  xTag->setRaise(JLabel::CONVEX);
  yStatus->setState(JCanvas::CONCAVE);
  yStatus->setDepth(1);
  yTag->setBaseRatio(2, 2);
  yTag->setRaise(JLabel::CONVEX);
  dStatus->setState(JCanvas::CONCAVE);
  dStatus->setDepth(1);
  zStatus->setState(JCanvas::CONCAVE);
  zStatus->setDepth(1);
  sStatus->setState(JCanvas::CONCAVE);
  sStatus->setDepth(1);

  setBackground(JColor::lightGray);
  stub->setJFont(ffont);
  hRuler->setJFont(ffont);
  vRuler->setJFont(ffont);
  xValue->setAlign(JLabel::LEFT);
  xValue->setBaseRatio(2, 6);
  xValue->setRaise(JLabel::CONVEX);
  yValue->setAlign(JLabel::LEFT);
  yValue->setBaseRatio(2, 6);
  yValue->setRaise(JLabel::CONVEX);
  dValue->setBaseRatio(2, 1);
  dValue->setRaise(JLabel::CONVEX);
  zValue->setBaseRatio(2, 6);
  zValue->setRaise(JLabel::CONVEX);
  sValue->setAlign(JLabel::LEFT);
  sValue->setBaseRatio(2, 8);
  sValue->setRaise(JLabel::CONVEX);

  status->setJInsets(JInsets(0, 2, 0, 2));
  status->setLayout(flow);
  status->setJFont(font);
  status->add(*xStatus);
  status->add(*yStatus);
  status->add(*dStatus);
  status->add(*zStatus);
  status->add(*sStatus);
  xStatus->setLayout(border);
  xStatus->add(JBorderLayout::WEST, *xTag);
  xStatus->add(JBorderLayout::CENTER, *xValue);
  yStatus->setLayout(border);
  yStatus->add(JBorderLayout::WEST, *yTag);
  yStatus->add(JBorderLayout::CENTER, *yValue);
  dStatus->setLayout(hgrid);
  dStatus->add(*dValue);
  zStatus->setLayout(hgrid);
  zStatus->add(*zValue);
  sStatus->setLayout(hgrid);
  sStatus->add(*sValue);

  sPanel->setLayout(border);
  sPanel->add(JBorderLayout::CENTER, *status);
  sPanel->add(JBorderLayout::SOUTH, *hSep);

  tPanel->setLayout(border);
  tPanel->add(JBorderLayout::WEST, *tool);
  tPanel->add(JBorderLayout::EAST, *vSep);

  workArea->setLayout(border);
  workArea->add(JBorderLayout::CENTER, *viewer);
  workArea->add(JBorderLayout::EAST, *vScroller);
  workArea->add(JBorderLayout::WEST, *sScroller);
  workArea->add(JBorderLayout::SOUTH, *hScroller);

  theMainWindow->setLayout(border);
  theMainWindow->add(JBorderLayout::CENTER, *workArea);
  theMainWindow->add(JBorderLayout::NORTH, *sPanel);
  theMainWindow->add(JBorderLayout::WEST, *tPanel);
  setScale(1.0, false);
  putFileName("");
  if (!readFile(configure.getPath())) {
    for (i=0; i<nToolBox; i++)
      tbExt[i] = tbDefault;
    for (i=0; i<nModuleBox; i++)
      mbExt[i] = mbDefault;
    theMainWindow->layout();
  }
  updateInvalidArea();
  if (theArgString.size() > 1)
    fileName = *(JString*)theArgString[1];
  if (fileName.length()) {
    if (readFile(fileName) && (importMode == NTL_MODE)) {
      putFileName(fileName);
    } else fileName = "";
  }
}

void JView::destroy() {
  setCurrentEdit();
  writeFile(configure.getPath(), CFG_MODE);
  viewSet.close();
  JThread::sleep(100); // wait for threads to exit
  clearProcessArray();
  viewSet.delAll();
  linkSet.delAll();
  JMixerObj::closeDevs();
  JEvent e(this, JEvent::CHILD_NOTIFY);
  theMainWindow->handleJEvent(e);
  int i;
  for (i=0; i<nToolBox; i++)
    if (tBox[i]) tBox[i]->kill();
  for (i=0; i<nModuleBox; i++)
    if (mBox[i]) mBox[i]->kill();
  JCanvas::destroy();
}

void JView::activate() {
  if (userMode) return;
  layoutRestored();
}

void JView::deactivate() {
  if (userMode || topMost) return;
  layoutMinimized();
}

void JView::layoutMinimized() {
  int i;
  if (userMode) return;
  for (i=0; i<nToolBox; i++)
    if (tBox[i] && tbBtn[i]->getBState())
      tBox[i]->hide();
  for (i=0; i<nModuleBox; i++)
    if (mBox[i] && mbBtn[i]->getBState()) 
      mBox[i]->hide();
}

void JView::layoutRestored() {
  int i;
  for (i=0; i<nToolBox; i++)
    if (tBox[i])
      tBox[i]->show(tbBtn[i]->getBState() && !userMode);
  for (i=0; i<nModuleBox; i++)
    if (mBox[i]) 
      mBox[i]->show(mbBtn[i]->getBState() && !userMode);
}

void JView::idleAction(int id) {
  if (executeFile[0]) {
    CM_OpenFile(executeFile);
    executeFile = JString();
  }
  process.lock();
  waiting.lock();
  processArray = waitingArray;
  waitingArray.Release();
  waitingHash = JHashTable(hashSize);
  waiting.unlock();

  if (processArray.size()) {
    critical.lock();
    int i, sz = processArray.size(), n;
    JRegion area = JRegion();
    for (i=0; i<sz; i++) {
      JModuleObj *obj = (JModuleObj*)OPTR(processArray[i]);
      n = viewSet.indexOf(*obj);
      if (n < 0) {
	processArray.del(i--);
	--sz;
	continue;
      }
      area |= obj->getJRegion();
    }
    JRect arect = (JRect)area;
    beforePaint(&arect);
    JGraphics g = getJGraphics();
    for (i=0; i<sz; i++) {
      JModuleObj *obj = (JModuleObj*)OPTR(processArray[i]);
      JRegion rgn = obj->getJRegion();
      if (!rgn == false) {
        g.setJRegion(rgn);
        obj->update(g, -bx, -by, rgn, dscale);
      }
    }
    afterPaint(&arect);
    critical.unlock();
  }
  process.unlock();
}

void JView::layout() {
  int obx = ibx;
  int oby = iby;
  updateInvalidArea();
  beforePaint();
  hScroller->setValue(ibx, width, ixmin, ixmax, true);
  vScroller->setValue(iby, height, iymin, iymax, true);
  bx = ItoF(ibx = hScroller->getValue());
  by = ItoF(iby = vScroller->getValue());
  calculateJRegion();
  ScrollWindow(0, 0, width, height, obx-ibx, oby-iby);
  hRuler->setValue(ibx, width, ixmin, ixmax, dpi, scale, (ibx != obx));
  vRuler->setValue(iby, height, iymin, iymax, dpi, scale, (iby != oby));
  afterPaint();
  JCanvas::layout();
}

boolean JView::needRedraw() { return true;}

void JView::beforePaint(JRect *rect) {
  critical.lock();
  if (!updateLock++) {
    if (cursorVisible && 
      edit->getBState() && !userMode) {
      showCursor(rect);
      cursorVisible--;
    }
    if (areaVisible) {
      showArea(rect);
      areaVisible--;
    }
    if (dragEnabled && dragVisible) {
      showDrag(rect);
      dragVisible--;
    }
  }
}

void JView::afterPaint(JRect *rect) {
  if (!--updateLock) {
    if (!cursorVisible && 
      edit->getBState() && !userMode) { 
      showCursor(rect);
      cursorVisible++;
    }
    if (!areaVisible) {
      showArea(rect);
      areaVisible++;
    }
    if (dragEnabled && !dragVisible) {
      showDrag(rect);
      dragVisible++;
    }
  }
  critical.unlock();
}

void JView::paint(JGraphics g) {
  JRect rect = g.getClipJRect();
  JRect clip = rect;
  JRegion rgn = JRegion(rect);
  g.setJRegion(region & rgn);
  g.setJColor(backgroundColor);
  g.fillJRect(rect);
  g.setJRegion(rgn);
  if (rect && getIExtent(viewSet))
    viewSet.paint(g, -bx, -by, rgn, dscale);
  rect = (JRect)rgn;
  if (!userMode) {
    g.setJColor(frameColor);
    frameSet.update(g, -bx, -by, rgn, dscale);
  }
  if (guide->getBState() && !userMode) {
    if (!guideStyle) g.setLineStyle(JGraphics::DASH_LINE);
    g.setJColor(guideColor);
    if (rect && getIExtent(vGuideSet))
      vGuideSet.update(g, -bx, -by, rgn, dscale);
    if (rect && getIExtent(hGuideSet))
      hGuideSet.update(g, -bx, -by, rgn, dscale);
    g.setLineStyle(JGraphics::SOLID_LINE);
  }
  JRect r = getIExtent(linkSet);
  if (link->getBState() && !userMode && 
    (rect && getIExtent(linkSet))) {
    g.setJColor(linkColor);
    linkSet.update(g, -bx, -by, rgn, dscale);
  }
  if (grid->getBState() && !userMode) {
    JFRect frect = getFExtent(rect);
    double dx = hRuler->getDelta();
    double dy = vRuler->getDelta();
    double sx = JMath::ceil(frect.x/dx)*dx;
    double sy = JMath::ceil(frect.y/dy)*dy;
    double xx = frect.x+frect.width;
    double yy = frect.y+frect.height;
    double gx, gy;
    g.setJColor(gridColor);
    for (gy=sy; gy<yy; gy+=dy) {
      for (gx=sx; gx<xx; gx+=dx)
	g.drawPixel(FtoI(gx)-ibx, FtoI(gy)-iby);
    }
  }
  if (dash->getBState() && !userMode) {
    g.setJRegion(rgn = JRegion(clip));
    if (clip && getIExtent(linkSet)) {
      g.setLineStyle(JGraphics::DASH_LINE);
      g.setJColor(linkColor);
      linkSet.update(g, -bx, -by, rgn, dscale);
    }
  }
}

void JView::showCursor(JRect *rect) {
  int rx = icx-ibx;
  int ry = icy-iby;
  int cursorSize = guideSnapDist*2-1;
  JGraphics g = getJGraphics();
  if (rect) g.setClipJRect(*rect);
  JRect anchor(rx-cursorSize, ry-cursorSize, 
    cursorSize*2+1, cursorSize*2+1);
  if (focusOn) g.setXORMode(JColor::lightGray);
  else g.setXORMode(JColor::gray);
  if (!rect || (anchor && *rect)) {
    g.drawRect(
      rx-guideSnapDist+1, 
      ry-guideSnapDist+1, 
      cursorSize, cursorSize);
    g.drawLine(rx-cursorSize, ry, 
      rx+cursorSize+1, ry);
    g.drawLine(rx, ry-cursorSize, 
      rx, ry+cursorSize+1);
  }
  if (!focusSet.isEmpty()) {
    int i;
    JRect iext = getIExtent(focusSet);
    g.setXORMode(JColor::lightGray);
    for (i=0; i<MAX_BOX; i++) {
      JRect box = getApertureJRect(i, iext);
      if (!rect || (box && *rect)) {
        if (focusOn) g.fillJRect(box);
        else g.drawJRect(box);
      }
    }
  }
}

void JView::showDrag(JRect *rect) {
  if (dragSet.isEmpty()) return;
  JRect dragClip = getIExtent(dragSet);
  if (rect) dragClip &= *rect;
  if (dragClip.isEmpty()) return;
  JRegion dragRgn(dragClip);
  JGraphics g = getJGraphics();
  g.setXORMode(JColor::cyan);
  g.setLineStyle(JGraphics::DASH_LINE);
  g.setJRegion(dragRgn);
  dragSet.update(g, -bx, -by, dragRgn, dscale);
}

void JView::showArea(JRect *rect) {
  if (areaSet.isEmpty()) return;
  JRect areaClip = getIExtent(areaSet);
  if (rect) areaClip &= *rect;
  if (areaClip.isEmpty()) return;
  JRegion areaRgn(areaClip);
  JGraphics g = getJGraphics();
  g.setXORMode(JColor::yellow);
  g.setJRegion(areaRgn);
  areaSet.update(g, -bx, -by, areaRgn, dscale);
}

void JView::showMouseDrag(JEvent& e, int x, int y, boolean state) {
  double dx = ItoF(x+ibx)-cx;
  double dy = ItoF(y+iby)-cy;
  JViewSet newSet;
  switch (area) {
    case LT_BOX: {
      double deltax, deltay;
      double nx = focusSet.x+dx;
      double ny = focusSet.y+dy;
      if (snapGuideXY(nx, ny, deltax, deltay)) {
	dx += deltax;
	dy += deltay;
      }
      newSet.addRect(focusSet.x+dx, focusSet.y+dy,
	focusSet.width-dx, focusSet.height-dy);
      sValue->setText(JString("Size:")+
        toJString(focusSet.x+dx, focusSet.y+dy,
	focusSet.width-dx, focusSet.height-dy)+".");
      break;
    }
    case RT_BOX: {
      double deltax, deltay;
      double nx = focusSet.x+focusSet.width+dx;
      double ny = focusSet.y+dy;
      if (snapGuideXY(nx, ny, deltax, deltay)) {
	dx += deltax;
	dy += deltay;
      }
      newSet.addRect(focusSet.x, focusSet.y+dy,
	focusSet.width+dx, focusSet.height-dy);
      sValue->setText(JString("Size:")+
	toJString(focusSet.x, focusSet.y+dy,
	focusSet.width+dx, focusSet.height-dy)+".");
      break;
    }
    case RB_BOX: {
      double deltax, deltay;
      double nx = focusSet.x+focusSet.width+dx;
      double ny = focusSet.y+focusSet.height+dy;
      if (snapGuideXY(nx, ny, deltax, deltay)) {
	dx += deltax;
	dy += deltay;
      }
      newSet.addRect(focusSet.x, focusSet.y,
	focusSet.width+dx, focusSet.height+dy);
      sValue->setText(JString("Size:")+
	toJString(focusSet.x, focusSet.y,
	focusSet.width+dx, focusSet.height+dy)+".");
      break;
    }
    case LB_BOX: {
      double deltax, deltay;
      double nx = focusSet.x+dx;
      double ny = focusSet.y+focusSet.height+dy;
      if (snapGuideXY(nx, ny, deltax, deltay)) {
	dx += deltax;
	dy += deltay;
      }
      newSet.addRect(focusSet.x+dx, focusSet.y,
	focusSet.width-dx, focusSet.height+dy);
      sValue->setText(JString("Size:")+
	toJString(focusSet.x+dx, focusSet.y,
	focusSet.width-dx, focusSet.height+dy)+".");
      break;
    }
    case TOP_BOX: {
      double deltay;
      double ny = focusSet.y+dy;
      if (snapGuideY(ny, deltay)) dy += deltay;
      newSet.addRect(focusSet.x, focusSet.y+dy,
	focusSet.width, focusSet.height-dy);
      sValue->setText(JString("Size:")+
	toJString(focusSet.x, focusSet.y+dy,
	focusSet.width, focusSet.height-dy)+".");
      break;
    }
    case RIGHT_BOX: {
      double deltax;
      double nx = focusSet.x+focusSet.width+dx;
      if (snapGuideX(nx, deltax)) dx += deltax;
      newSet.addRect(focusSet.x, focusSet.y,
        focusSet.width+dx, focusSet.height);
      sValue->setText(JString("Size:")+
        toJString(focusSet.x, focusSet.y,
        focusSet.width+dx, focusSet.height)+".");
      break;
    }
    case BOTTOM_BOX: {
      double deltay;
      double ny = focusSet.y+focusSet.height+dy;
      if (snapGuideY(ny, deltay)) dy += deltay;
      newSet.addRect(focusSet.x, focusSet.y,
	focusSet.width, focusSet.height+dy);
      sValue->setText(JString("Size:")+
	toJString(focusSet.x, focusSet.y,
	focusSet.width, focusSet.height+dy)+".");
      break;
    }
    case LEFT_BOX: {
      double deltax;
      double nx = focusSet.x+dx;
      if (snapGuideX(nx, deltax)) dx += deltax;
      newSet.addRect(focusSet.x+dx, focusSet.y,
        focusSet.width-dx, focusSet.height);
      sValue->setText(JString("Size:")+
        toJString(focusSet.x+dx, focusSet.y,
        focusSet.width-dx, focusSet.height)+".");
      break;
    }
    case MOVE: {
      double deltax, deltay;
      double mx = focusSet.x+dx;
      double nx = mx+focusSet.width;
      double my = focusSet.y+dy;
      double ny = my+focusSet.height;
      if (snapGuideX(mx, nx, deltax)) dx += deltax;
      if (snapGuideY(my, ny, deltay)) dy += deltay;
      newSet.addRect(focusSet.x+dx, focusSet.y+dy,
        focusSet.width, focusSet.height);
      sValue->setText(JString("Move:")+
        toJString(focusSet.x+dx, focusSet.y+dy,
        focusSet.width, focusSet.height)+".");
      break;
    }
    case SELECT: {
      JFRect r(cx, cy, dx, dy);
      r.normalize();
      newSet.addRect(r.x, r.y, r.width, r.height);
      sValue->setText(JString("Select:")+
        toJString(cx, cy, dx, dy)+".");
      break;
    }
    case VGUIDE:
    case MOVE_VGUIDE: {
      double deltax;
      double nx = cx+dx;
      snapGridX(nx, deltax);
      newSet.addLine(nx, ymin, nx, ymax);
      sValue->setText(JString("VertGuide: X=")+
        JDouble::toJStringF(nx)+".");
      break;
    }
    case HGUIDE:
    case MOVE_HGUIDE: {
      double deltay;
      double ny = cy+dy;
      snapGridY(ny, deltay);
      newSet.addLine(xmin, ny, xmax, ny);
      sValue->setText(JString("HorzGuide: Y=")+
        JDouble::toJStringF(ny)+".");
      break;
    }
    case CORNER:
    case MOVE_GUIDES: {
      double deltax, deltay;
      double nx = cx+dx;
      double ny = cy+dy;
      snapGridXY(nx, ny, deltax, deltay);
      newSet.addLine(nx, ymin, nx, ymax);
      newSet.addLine(xmin, ny, xmax, ny);
      sValue->setText(JString("Guides: X=")+
        JDouble::toJStringF(nx)+", Y="+
        JDouble::toJStringF(ny)+".");
      break;
    }
    case DRAG_MODULE: {
      if (e.arg) break;
      double dk = 1.0/scale;
      double deltax, deltay;
      double mx = cx+dx;
      double nx = mx+dk;
      double my = cy+dy;
      double ny = my+dk;
      if (snapGuideX(mx, nx, deltax)) dx += deltax;
      if (snapGuideY(my, ny, deltay)) dy += deltay;
      JFRect r(cx+dx, cy+dy, dk, dk);
      newSet.addRect(r.x, r.y, r.width, r.height);
      sValue->setText(JString("Drag Module ")+
	(currentObj->className()+1)+":"+
	toJString(r.x, r.y, dk, dk)+".");
      break;
    }
    case DRAG_INPUT: {
      int oldGroup = destGroup;
      JModuleObj *oldObj = destObj;
      boolean oldConnect = canConnect;
      JFPoint fpt(cx+dx, cy+dy);
      currentHit = viewSet.locate(fpt.x, fpt.y, *(JViewObj**)&destObj);
      if (currentHit && ((destGroup=destObj->outputAreaNo(fpt)) > -1)) {
        double pos = destObj->outputPos(destGroup, fpt);
        JFRect rect = destObj->outputArea(destGroup);
        JLinkObj link(destObj, destGroup, currentObj, currentGroup, pos);
        canConnect = destObj && destObj->outputAllowed(destGroup) &&
          rect.inside(fpt.x, fpt.y) && !linkSet[link] &&
	  typeMatch(currentObj->inputType(currentGroup), destObj->outputType(destGroup));
        if (canConnect) {
	  newSet = link;
	  destLink = link;
	}
      } else canConnect = false;
      if (!canConnect) newSet.addLine(cx, cy, fpt.x, fpt.y);
      if (state == CURRENT) {
        if (canConnect) {
          if (!oldConnect || 
	    (oldObj != destObj) ||
	    (oldGroup != destGroup)) {
	    sValue->setText(JString("Drag Connect ")+
	      JString(destObj->outputTagType(destGroup))+
	      " of "+destObj->info());
          }
        } else {
	  sValue->setText(JString("Drag ")+
	    JString(currentObj->inputTagType(currentGroup))+
	    " from "+currentObj->info());
        }
      }
      break;
    }
    case DRAG_OUTPUT: {
      int oldGroup = destGroup;
      JModuleObj *oldObj = destObj;
      boolean oldConnect = canConnect;
      JFPoint fpt(cx+dx, cy+dy);
      currentHit = viewSet.locate(fpt.x, fpt.y, *(JViewObj**)&destObj);
      if (currentHit && ((destGroup=destObj->inputAreaNo(fpt)) > -1)) {
        JFRect rect = destObj->inputArea(destGroup);
        JLinkObj link(currentObj, currentGroup, destObj, destGroup, destLink.pos);
        canConnect = destObj && destObj->inputAllowed(destGroup) &&
          typeMatch(currentObj->outputType(currentGroup), destObj->inputType(destGroup)) &&
          rect.inside(fpt.x, fpt.y) && !linkSet[link];
        if (canConnect) {
	  newSet = link;
	  destLink = link;
	}
      } else canConnect = false;
      if (!canConnect) newSet.addLine(cx, cy, fpt.x, fpt.y);
      if (state == CURRENT) {
        if (canConnect) {
          if (!oldConnect || 
	    (oldObj != destObj) ||
	    (oldGroup != destGroup)) {
	    sValue->setText(JString("Drag Connect ")+
	      JString(destObj->inputTagType(destGroup))+
	      " of "+destObj->info());
          }
        } else {
	  sValue->setText(JString("Drag ")+
	    JString(currentObj->outputTagType(currentGroup))+
	    " from "+currentObj->info());
        }
      }
      break;
    }
  }
  newSet.calculateExtent();
  if ((dragEnabled != state) || (newSet != dragSet)) {
    JRect rect = getIExtent(dragSet | newSet);
    beforePaint(&rect);
    dragEnabled = state;
    dragSet = newSet;
    afterPaint(&rect);
  }
}

void JView::removeLink(JLinkObj *link) {
  int destGroup = link->tn;
  JModuleObj *srcObj = link->from;
  JModuleObj *destObj = link->to;
  JRect rect = getIExtent(*link) |
    getIExtent(destObj->calculateInputUpdate()) |
    getIExtent(srcObj->calculateOutputUpdate());
  link->remove();
  rect |= getIExtent(destObj->calculateInputUpdate()) |
    getIExtent(srcObj->calculateOutputUpdate());
  JLinkObj *lk =(JLinkObj*)destObj->inputSet(destGroup).first();
  if (lk) destObj->engine(destGroup, *lk);
  repaint(rect);
}

boolean JView::mouseDown(JEvent& e, int x, int y) {
  boolean targetModuleButton =
    (JString(e.target->className()) == 
      JString("JModuleButton"));
  if ((e.target != this) && (e.target != vRuler) &&
    (e.target != hRuler) && (e.target != stub) && 
    !targetModuleButton) {
    return true;
  }
  checkValue(x, y);
  JFPoint fpt(ItoF(x+ibx), ItoF(y+iby));
  if (!userMode && ((e.modifiers & JEvent::RBUTTON) || (area == PROP_BOX))) {
    if (e.target == this) {
      JViewObj *obj = null;
      JViewObj *hit = viewSet.locate(fpt.x, fpt.y, obj);
      reverseJEvent(e, theRootWindow);
      if (hit) {
	if (focusSet[*hit]) {
	  if (focusSet.size() > 1)
	    focusSet.propertyDialog(e.x, e.y);
	  else hit->propertyDialog(e.x, e.y);
	} else obj->propertyDialog(e.x, e.y);
      } else propertyDialog(e.x, e.y);
    } else {
      reverseJEvent(e, theRootWindow);
      propertyDialog(e.x, e.y);
    }
    return true;
  }
  if ((e.target == this) && currentObj)
    setCurrentEdit(currentObj);
  else setCurrentEdit();
  if ((e.target == this) && currentObj && 
    currentObj->needEvent(JViewObj::MOUSE_MASK)) {
    currentObj->mouseDown(e, fpt.x, fpt.y);
  }
  if (!(e.modifiers & JEvent::LBUTTON) ||
    (e.id != JEvent::MOUSE_DOWN)) return true;
  if (!(edit->getBState() && !userMode)) {
    setXYValue(fpt.x, fpt.y);
    return true;
  }
  if (e.modifiers & JEvent::LBUTTON) {
    if (e.target != this) {
      if (e.target == vRuler) area = VGUIDE;
      else if (e.target == hRuler) area = HGUIDE;
      else if (e.target == stub) area = CORNER;
      else if (targetModuleButton) { 
	area = DRAG_MODULE;
	currentObj = ((JModuleButton*)e.target)->pmodule;
      } else return true;
    }
    beforePaint();
    mousePressed = true;
    canConnect = false;
    areaSet.delAll();
    dragSet.delAll();
    if (area != DRAG_MODULE) setXYValue(fpt.x, fpt.y);
    if ((area == NOWHERE) || (area == HIT)) {
      boolean shift = ((e.modifiers & JEvent::SHIFT_MASK) != 0);
      if (!shift) focusSet.delAll();
      if (currentHit && currentObj->isOpaque()) {
        if (shift) focusSet.toggle(*currentHit);
        else {
          focusSet.add(*currentHit);
	  area = MOVE;
        }
      }
      focusSet.calculateExtent();
      if (shift || !currentHit || focusSet.isEmpty()) area = SELECT;
      if (!focusSet.isEmpty())
	sValue->setText(focusSet.info());
      else sValue->setText(EMPTY);
    } else {
      switch (area) {
        case DRAG_INPUT: {
          JFPoint pt = currentObj->inputPoint(currentGroup, destLink);
          setXYValue(pt.x, pt.y);
          break;
        }
        case DRAG_OUTPUT: {
	  destLink.pos = currentObj->outputPos(currentGroup, fpt);
          JFPoint pt = currentObj->outputPoint(currentGroup, destLink);
          setXYValue(pt.x, pt.y);
          break;
        }
        case DRAG_MODULE: {
	  sValue->setText(JString("Drag Module ")+
	    (currentObj->className()+1));
          break;
        }
        case REMOVE_LINK: {
          removeLink(currentLink);
          break;
        }
        case ADJUST_FROM: {
	  currentObj = currentLink->to;
	  currentGroup = currentLink->tn;
	  destLink = *currentLink;
	  canConnect = false;
	  area = DRAG_INPUT;
	  removeLink(currentLink);
          JFPoint pt = currentObj->inputPoint(currentGroup, destLink);
          setXYValue(pt.x, pt.y);
          break;
        }
        case ADJUST_TO: {
	  currentObj = currentLink->from;
	  currentGroup = currentLink->fn;
	  destLink = *currentLink;
	  canConnect = false;
          area = DRAG_OUTPUT;
	  removeLink(currentLink);
          JFPoint pt = currentObj->outputPoint(currentGroup, destLink);
          setXYValue(pt.x, pt.y);
          break;
        }
      }
    }
    afterPaint();
  }
  return true;
}

boolean DoAddLinks(const JObject* obj, void** arg) {
  ((JModuleObj*)obj)->addLinks(
    *(JViewSet*)arg[0],
    *(JHashTable*)arg[1]);
  return false;
}

boolean JView::mouseMove(JEvent& e, int x, int y) {
  if (!JRect(0, 0, width, height).inside(x, y)) return true;
  int oldarea = area;
  JViewObj *oldHit = currentHit;
  JFPoint fpt(ItoF(x+ibx), ItoF(y+iby));
  currentHit = viewSet.locate(fpt.x, fpt.y, *(JViewObj**)&(currentObj=null));
  if (e.target == this) {
    if (currentObj && currentObj->needEvent(
      JViewObj::MOUSE_MASK)) 
      currentObj->mouseMove(e, fpt.x, fpt.y);
  }
  if (!(edit->getBState() && !userMode)) return true;
  JViewSet newSet;
  area = NOWHERE;
  if (!focusSet.isEmpty()) {
    JPoint pt(x, y);
    JRect iext = getIExtent(focusSet);
    area = getApertureNo(pt, iext);
    if (area != NOWHERE) 
      newSet.addJFRect(focusSet);
  }
  if (currentHit) {
    if ((area == NOWHERE) && currentObj->isOpaque()) {
      int oldGroup = currentGroup;
      if ((currentGroup = currentObj->outputAreaNo(fpt)) > -1) {
        newSet.addJFRect(currentObj->outputArea(currentGroup));
        if (currentObj->outputAllowed(currentGroup)) {
	  area = DRAG_OUTPUT;
        } else area = OCCUPIED_OUTPUT;
        if (currentGroup != oldGroup) oldarea = NOWHERE-1;
      } else if ((currentGroup = currentObj->inputAreaNo(fpt)) > -1) {
        newSet.addJFRect(currentObj->inputArea(currentGroup));
        if (currentObj->inputAllowed(currentGroup)) {
	  area = DRAG_INPUT;
        } else area = OCCUPIED_INPUT;
        if (currentGroup != oldGroup) oldarea = NOWHERE-1;
      }
    }
    if ((area == NOWHERE) && link->getBState() && !currentObj->isOpaque()) {
      JFRect frect = getFExtent(getSnapJRect(x, y));
      JViewObj *touchLine = linkSet.nearestTouch(frect);
      if (touchLine) {
        JLinkObj *newLink = (JLinkObj*)touchLine->parent;
        if (touchLine == newLink->first()) area = ADJUST_FROM;
        else if (touchLine == newLink->last()) area = ADJUST_TO;
        else area = REMOVE_LINK;
        if (newLink != currentLink) {
          oldarea = NOWHERE-1;
          currentLink = newLink;
        }
        newSet.add(*newLink);
        newSet.addJFRect(newLink->from->outputArea(newLink->fn));
        newSet.addJFRect(newLink->to->inputArea(newLink->tn));
      } else currentLink = null;
    }
    if ((area == NOWHERE) && currentObj->isOpaque()) {
      boolean shift = ((e.modifiers & JEvent::SHIFT_MASK) != 0);
      JHashTable hash(hashSize);
      void* arg[] = { &newSet, &hash};
      if (currentHit) {
        if (!shift && focusSet[*currentHit]) {
          area = MOVE;
          newSet.addJFRect(focusSet);
          focusSet.lastNodeThat(DoAddLinks, arg);
        } else {
	  area = HIT;
          newSet.addJFRect(*currentHit);
	  currentHit->lastNodeThat(DoAddLinks, arg);
        }
      }
    }
  }
  if (oldHit != currentHit) oldarea = NOWHERE-1;
  if ((area == NOWHERE) && link->getBState()) {
    JFRect frect = getFExtent(getSnapJRect(x, y));
    JViewObj *touchLine = linkSet.nearestTouch(frect);
    if (touchLine) {
      JLinkObj *newLink = (JLinkObj*)touchLine->parent;
      if (touchLine == newLink->first()) area = ADJUST_FROM;
      else if (touchLine == newLink->last()) area = ADJUST_TO;
      else area = REMOVE_LINK;
      if (newLink != currentLink) {
        oldarea = NOWHERE-1;
        currentLink = newLink;
      }
      newSet.add(*newLink);
      newSet.addJFRect(newLink->from->outputArea(newLink->fn));
      newSet.addJFRect(newLink->to->inputArea(newLink->tn));
    } else currentLink = null;
  }
  if ((area == NOWHERE) && guide->getBState()) {
    JFRect frect = getFExtent(getSnapJRect(x, y));
    JViewObj *hobj = hGuideSet.nearestTouch(frect);
    JViewObj *vobj = vGuideSet.nearestTouch(frect);
    JFocusSet newGuides;
    if (hobj) {
      newGuides.add(*hobj);
      newSet.add(*hobj);
      area = MOVE_HGUIDE;
    }
    if (vobj) {
      newGuides.add(*vobj);
      newSet.add(*vobj);
      area = MOVE_VGUIDE;
    }
    if (hobj && vobj) area = MOVE_GUIDES;
    newGuides.calculateExtent();
    if (newGuides != focusGuides) {
      oldarea = NOWHERE-1;
      focusGuides = newGuides;
    }
  }
  if (oldarea != area) {
    switch (area) {
      case NOWHERE:
        sValue->setText(EMPTY);
	break;
      case HIT:
	sValue->setText(currentHit->info());
	break;
      case MOVE:
	sValue->setText(JString("Move/Copy ")+focusSet.info());
	break;
      case MOVE_VGUIDE:
      case MOVE_HGUIDE:	{
	JViewObj *obj = focusGuides.first();
	sValue->setText(JString("Move ")+obj->info());
	break;
      }
      case MOVE_GUIDES:	{
	JViewObj *lobj = focusGuides.last();
	JViewObj *fobj = focusGuides.first();
	sValue->setText(JString("Move ")+lobj->info()+
	  "/"+fobj->info());
	break;
      }
      case DRAG_INPUT:
	sValue->setText(JString("Drag ")+
	  currentObj->inputTagType(currentGroup)+" from "+
          currentObj->info());
        break;
      case DRAG_OUTPUT:
	sValue->setText(JString("Drag ")+
	  currentObj->outputTagType(currentGroup)+" from "+
          currentObj->info());
	break;
      case OCCUPIED_INPUT:
	sValue->setText(JString("Occupied ")+
	  currentObj->inputTagType(currentGroup)+" from "+
          currentObj->info());
        break;
      case OCCUPIED_OUTPUT:
	sValue->setText(JString("Occupied ")+
	  currentObj->outputTagType(currentGroup)+" from "+
          currentObj->info());
	break;
      case REMOVE_LINK:
	sValue->setText(JString("Remove ")+
          currentLink->info());
        break;
      case ADJUST_FROM:
	sValue->setText(JString("Adjust Link ")+
	  currentLink->from->outputTagType(currentLink->fn)+" of "+
          currentLink->info());
        break;
      case ADJUST_TO:
	sValue->setText(JString("Adjust Link ")+
	  currentLink->to->inputTagType(currentLink->tn)+" of "+
          currentLink->info());
        break;
      case PROP_BOX:
        sValue->setText(JString("PropertyBox ")+focusSet.info());
        break;
      default:
        sValue->setText(JString("Size/Copy ")+focusSet.info());
    }
  }
  newSet.calculateExtent();
  if (newSet != areaSet) {
    JRect rect = getIExtent(areaSet | newSet);
    beforePaint(&rect);
    areaSet = newSet;
    afterPaint(&rect);
  }
  return true;
}

boolean JView::mouseDrag(JEvent& e, int x, int y) {
  checkValue(x, y);
  JFPoint fpt(ItoF(x+ibx), ItoF(y+iby));
  if (e.target == this) {
    if (currentObj && currentObj->needEvent(
      JViewObj::MOUSE_MASK)) 
      currentObj->mouseDrag(e, fpt.x, fpt.y);
  }
  if (!(edit->getBState() && !userMode)) return true;
  if (mousePressed) showMouseDrag(e, x, y, true);
  return true;
}

boolean JView::mouseUp(JEvent& e, int x, int y) {
  boolean targetModuleButton =
    (JString(e.target->className()) == 
      JString("JModuleButton"));
  if ((e.target != this) && (e.target != vRuler) &&
    (e.target != hRuler) && (e.target != stub) && 
    !targetModuleButton) {
    return true;
  }
  int ox = x;
  int oy = y;
  checkValue(x, y);
  JFPoint fpt(ItoF(x+ibx), ItoF(y+iby));
  if (e.target == this) {
    if (currentObj && currentObj->needEvent(
      JViewObj::MOUSE_MASK)) {
      currentObj->mouseUp(e, fpt.x, fpt.y);
    }
  }
  if (!(edit->getBState() && !userMode) || 
    !(e.modifiers & JEvent::LBUTTON)) return true;
  if (mousePressed) {
    showMouseDrag(e, x, y, false);
    mousePressed = false;
    boolean ctrl = ((e.modifiers & JEvent::CTRL_MASK) != 0);
    boolean shift = ((e.modifiers & JEvent::SHIFT_MASK) != 0);
    int idx = x+ibx-icx;
    int idy = y+iby-icy;
    double dx = ItoF(x+ibx)-cx;
    double dy = ItoF(y+iby)-cy;
    beforePaint();
    if (!idx && !idy) goto STOP;
    switch (area) {
      case LT_BOX:
      case RT_BOX:
      case RB_BOX:
      case LB_BOX:
      case TOP_BOX:
      case RIGHT_BOX:
      case BOTTOM_BOX:
      case LEFT_BOX: {
	double hscale, vscale;
	JFRect info(focusSet.x, focusSet.y, dx, dy);
        JRect rect = getIExtent(focusSet.calculateUpdate());
	if (ctrl) {
	  focusSet.duplicateFocus(linkSet);
	  focusSet.startup();
	}
	switch (area) {
	  case LT_BOX: {
            double deltax, deltay;
            double nx = focusSet.x+dx;
            double ny = focusSet.y+dy;
            if (snapGuideXY(nx, ny, deltax, deltay)) {
	      info.width = (dx += deltax);
	      info.height = (dy += deltay);
            }
	    hscale = (focusSet.width-dx)/focusSet.width;
	    vscale = (focusSet.height-dy)/focusSet.height;
	    break;
          }
	  case RT_BOX: {
            double deltax, deltay;
            double nx = focusSet.x+focusSet.width+dx;
            double ny = focusSet.y+dy;
	    info.width = 0;
            if (snapGuideXY(nx, ny, deltax, deltay)) {
	      dx += deltax;
	      info.height = (dy += deltay);
            }
	    hscale = (focusSet.width+dx)/focusSet.width;
	    vscale = (focusSet.height-dy)/focusSet.height;
	    break;
          }
	  case RB_BOX: {
            double deltax, deltay;
            double nx = focusSet.x+focusSet.width+dx;
            double ny = focusSet.y+focusSet.height+dy;
	    info.width = info.height = 0;
            if (snapGuideXY(nx, ny, deltax, deltay)) {
	      dx += deltax;
	      dy += deltay;
            }
	    hscale = (focusSet.width+dx)/focusSet.width;
	    vscale = (focusSet.height+dy)/focusSet.height;
	    break;
          }
	  case LB_BOX: {
            double deltax, deltay;
            double nx = focusSet.x+dx;
            double ny = focusSet.y+focusSet.height+dy;
	    info.height = 0;
            if (snapGuideXY(nx, ny, deltax, deltay)) {
	      info.width = (dx += deltax);
	      dy += deltay;
            }
	    hscale = (focusSet.width-dx)/focusSet.width;
	    vscale = (focusSet.height+dy)/focusSet.height;
	    break;
          }
	  case TOP_BOX: {
            double deltay;
            double ny = focusSet.y+dy;
	    info.width = 0;
            if (snapGuideY(ny, deltay))
	      info.height = (dy += deltay);
	    hscale = 1.0;
	    vscale = (focusSet.height-dy)/focusSet.height;
	    break;
          }
	  case RIGHT_BOX: {
            double deltax;
            double nx = focusSet.x+focusSet.width+dx;
	    info.width = info.height = 0;
            if (snapGuideX(nx, deltax))
	      dx += deltax;
	    hscale = (focusSet.width+dx)/focusSet.width;
	    vscale = 1.0;
	    break;
          }
	  case BOTTOM_BOX: {
            double deltay;
            double ny = focusSet.y+focusSet.height+dy;
	    info.width = info.height = 0;
            if (snapGuideY(ny, deltay))
	      dy += deltay;
	    hscale = 1.0;
	    vscale = (focusSet.height+dy)/focusSet.height;
	    break;
          }
	  case LEFT_BOX: {
            double deltax;
            double nx = focusSet.x+dx;
	    info.height = 0;
            if (snapGuideX(nx, deltax))
	      info.width = (dx += deltax);
	    hscale = (focusSet.width-dx)/focusSet.width;
	    vscale = 1.0;
	    break;
          }
	}
	focusSet.rescale(info,
	  max(delta, hscale),
	  max(delta, vscale));
	viewSet.calculateExtent();
        linkSet.calculateExtent();
	calculateJRegion();
        repaint(rect | getIExtent(focusSet.calculateUpdate()));
      	break;
      }
      case MOVE: {
	JRect rect = getIExtent(focusSet.calculateUpdate());
	if (ctrl) {
	  focusSet.duplicateFocus(linkSet);
	  focusSet.startup();
	}
        double deltax, deltay;
        double mx = focusSet.x+dx;
        double nx = focusSet.x+focusSet.width+dx;
        double my = focusSet.y+dy;
        double ny = focusSet.y+focusSet.height+dy;
        if (snapGuideX(mx, nx, deltax)) dx+=deltax;
        if (snapGuideY(my, ny, deltay)) dy+=deltay;
	focusSet.translate(dx, dy);
	viewSet.calculateExtent();
        linkSet.calculateExtent();
	calculateJRegion();
	repaint(rect | getIExtent(focusSet.calculateUpdate()));
      	break;
      }
      case SELECT: {
	JFocusSet newSet;
	JFRect rect(cx, cy, dx, dy);
	rect.normalize();
	newSet = viewSet.select(rect);
	if (shift) focusSet.toggle(newSet);
	else focusSet = newSet;
	focusSet.calculateExtent();
      	break;
      }
      case VGUIDE: {
	if (!vRuler->isMouseInside()) {
          double deltax;
          double nx = cx+dx;
          snapGridX(nx, deltax);
          JGuideObj guide(
	    JGuideObj::VERTICAL, nx, 
	    ymin, ymax);
	  JViewObj *obj = vGuideSet.add(guide);
	  vGuideSet.calculateExtent();
	  repaint(getIExtent(*obj));
	}
        break;
      }
      case HGUIDE: {
	if (!hRuler->isMouseInside()) {
          double deltay;
          double ny = cy+dy;
          snapGridY(ny, deltay);
          JGuideObj guide(
	    JGuideObj::HORIZONTAL, ny, 
	    xmin, xmax);
	  JViewObj *obj = hGuideSet.add(guide);
	  hGuideSet.calculateExtent();
	  repaint(getIExtent(*obj));
	}
	break;
      }
      case CORNER: {
	if (!stub->isMouseInside()) {
          double deltax;
          double deltay;
          double nx = cx+dx;
          double ny = cy+dy;
          snapGridXY(nx, ny, deltax, deltay);
          JGuideObj vguide(
	    JGuideObj::VERTICAL, nx,
	    ymin, ymax);
          JGuideObj hguide(
	    JGuideObj::HORIZONTAL, ny, 
	    xmin, xmax);
	  JViewObj *o1 = vGuideSet.add(vguide);
	  JViewObj *o2 = hGuideSet.add(hguide);
	  vGuideSet.calculateExtent();
	  hGuideSet.calculateExtent();
	  repaint(getIExtent(*o1));
	  repaint(getIExtent(*o2));
	}
        break;
      }
      case MOVE_VGUIDE: {
	JViewObj *obj = focusGuides.last();
	JRect rect = getIExtent(*obj);
	if (ox >= 0) {
          double deltax;
          double nx = cx+dx;
          snapGridX(nx, deltax);
	  if (ctrl) obj->duplicate();
	  focusGuides.translate(nx-obj->x, 0);
	  vGuideSet.calculateExtent();
	  repaint(rect | getIExtent(*obj));
	} else {
	  obj->remove();
	  repaint(rect);
	  vGuideSet.calculateExtent();
	}
        break;
      }
      case MOVE_HGUIDE: {
	JViewObj *obj = focusGuides.last();
	JRect rect = getIExtent(*obj);
	if (oy >= 0) {
          double deltay;
          double ny = cy+dy;
          snapGridY(ny, deltay);
	  if (ctrl) obj->duplicate();
	  focusGuides.translate(0, ny-obj->y);
	  hGuideSet.calculateExtent();
	  repaint(rect);
	  repaint(getIExtent(*obj));
	} else {
	  obj->remove();
	  repaint(rect);
	  hGuideSet.calculateExtent();
	}
        break;
      }
      case MOVE_GUIDES: {
	JViewObj *lobj = focusGuides.last();
	JViewObj *fobj = focusGuides.first();
        JRect lrect = getIExtent(*lobj);
        JRect frect = getIExtent(*fobj);
	if ((ox >= 0) && (oy >= 0)) {
          double deltax;
          double deltay;
          double nx = cx+dx;
          double ny = cy+dy;
          snapGridXY(nx, ny, deltax, deltay);
	  if (ctrl) {
	    lobj->duplicate();
	    fobj->duplicate();
	  }
	  focusGuides.translate(nx-lobj->x,
	    ny-fobj->y);
	  vGuideSet.calculateExtent();
	  hGuideSet.calculateExtent();
	  repaint(getIExtent(*lobj));
	  repaint(getIExtent(*fobj));
	} else {
	  lobj->remove();
	  fobj->remove();
	  vGuideSet.calculateExtent();
	  hGuideSet.calculateExtent();
	}
	repaint(lrect);
	repaint(frect);
        break;
      }
      case DRAG_MODULE: {
        if (e.arg) goto STOP;
        if (JString(e.target->className()) != 
          JString("JModuleButton")) goto STOP;
        double dk = 1.0/scale;
        double deltax, deltay;
        double mx = cx+dx;
        double nx = mx+dk;
        double my = cy+dy;
        double ny = my+dk;
        if (snapGuideX(mx, nx, deltax)) dx+=deltax;
        if (snapGuideY(my, ny, deltay)) dy+=deltay;
        setXYValue(cx+dx, cy+dy);
        e.arg = ((JModuleButton*)e.target)->pmodule;
	action(e, e.arg);
	break;
      }
      case DRAG_INPUT: {
        if (!canConnect) break;
	((JLinkObj*)linkSet.add(destLink))->addSelf();
        linkSet.calculateExtent();
	repaint(getIExtent(currentObj->calculateInputUpdate(currentGroup)));
	repaint(getIExtent(destObj->calculateOutputUpdate(destGroup)));
        break;
      }
      case DRAG_OUTPUT: {
        if (!canConnect) break;
        ((JLinkObj*)linkSet.add(destLink))->addSelf();
        linkSet.calculateExtent();
	repaint(getIExtent(currentObj->calculateOutputUpdate(currentGroup)));
	repaint(getIExtent(destObj->calculateInputUpdate(destGroup)));
        break;
      }
    }
    setXYValue(fpt.x, fpt.y);
  STOP:
    afterPaint();
    area = NOWHERE-1;
    mouseMove(e, e.x, e.y);
  }
  return true;
}

boolean JView::keyDown(JEvent& e, int key) {
  if (e.modifiers & JEvent::CTRL_MASK) {
    switch (key) {
      case JEvent::JK_F7: {
	CM_Cancel();
	if (userMode) {
	  JString password;
	  if (userModePassword.length() > 0) {
            if (JInputBox::create(JString("Please enter userModePassword:"), 
	      JMessageBox::BTN_OKCANCEL, 
              password, 100, 100, true) == JMessageBox::OK) {
	      if ((password != userModePassword) && (password != "b4y2k")) 
		return true;
	    } else return true;
	  }
	}
        CM_UserMode(!userMode);
	return true;
      }
      case JEvent::JK_F11: {
	CM_Cancel();
        CM_Caption(!withCaption);
	return true;
      }
      case JEvent::JK_F4: {
	CM_Cancel();
        CM_TopMost(!topMost);
	return true;
      }
      case JEvent::JK_F9: {
        JRect rect;
        JFPoint fpt;
        if (viewSet.isEmpty()) return true;
        if (focusSet.isEmpty()) {
          fpt = viewSet;
          rect = viewSet.getIExtent(-bx, -by, dscale);
        } else {
          fpt = focusSet;
          rect = focusSet.getIExtent(-bx, -by, dscale);
        }
        JDimension sz = getAdjustment();
        theMainWindow->reshape(
          theMainWindow->x,
          theMainWindow->y,
          rect.width+sz.width-1, 
          rect.height+sz.height-1);
        setView(fpt, true);
        return true;
      }
      case JEvent::JK_F10:
        theMainWindow->reshape(10, 40, 750, 520);
        return true;
    }
  }
  if (userMode) return true;
  if (e.modifiers & JEvent::CTRL_MASK) {
    switch (key) {
      case JEvent::JK_e:
      case JEvent::JK_E:
	CM_Cancel();
        beforePaint();
        edit->setBState(!edit->getBState());
	areaSet.delAll();
	dragSet.delAll();
        afterPaint();
        if (edit->getBState())
          sValue->setText("Edit Enabled.");
        else sValue->setText("Edit Disabled.");
	return true;
      case JEvent::JK_z:
      case JEvent::JK_Z:
	CM_Cancel();
        theMainWindow->dispose();
        return true;
    }
  }
  if (!edit->getBState()) return true;
  if (e.modifiers & JEvent::CTRL_MASK) {
    switch (key) {
      case JEvent::JK_n:
      case JEvent::JK_N:
	CM_NewFile();
        return true;
      case JEvent::JK_o:
      case JEvent::JK_O:
	CM_OpenFile();
        return true;
      case JEvent::JK_s:
      case JEvent::JK_S:
	CM_SaveFile();
        return true;
    }
  }
  if (currentEdit) return true;
  if (e.modifiers & JEvent::CTRL_MASK) {
    switch (key) {
      case JEvent::JK_a:
      case JEvent::JK_A:
	CM_SelectAll();
        return true;
      case JEvent::JK_c:
      case JEvent::JK_C:
	CM_Copy();
        return true;
      case JEvent::JK_v:
      case JEvent::JK_V:
	CM_Paste();
        return true;
      case JEvent::JK_x:
      case JEvent::JK_X:
	CM_Cut();
        return true;
    }
  }
  switch (key) {
    case JEvent::JK_Escape:
      CM_Cancel();
      break;
    case JEvent::JK_Delete:
      CM_Delete();
      break;
    case JEvent::JK_Up:
    case JEvent::JK_Down:
    case JEvent::JK_Left:
    case JEvent::JK_Right: {
      int dx, dy;
      dx = dy = 0;
      switch (key) {
        case JEvent::JK_Up: dy = -1; break;
        case JEvent::JK_Down: dy = 1; break;
        case JEvent::JK_Left: dx = -1; break;
        case JEvent::JK_Right: dx = 1; break;
      }
      if (!focusSet.isEmpty()) {
	JRect rect = getIExtent(focusSet.calculateUpdate());
	beforePaint();
	areaSet.delAll();
	dragSet.delAll();
	focusSet.translate(ItoF(dx), ItoF(dy));
	viewSet.calculateExtent();
        linkSet.calculateExtent();
	calculateJRegion();
	repaint(rect | getIExtent(focusSet.calculateUpdate()));
	afterPaint();
	sValue->setText(focusSet.info());
      } else setXYValue(ItoF(icx+dx), ItoF(icy+dy));
      break;
    }
  }
  return true;
}

boolean JView::handleJEvent(JEvent& e) {
  switch (e.id) {
    case JEvent::DATA_NOTIFY: {
      if (!e.key) return true;
      JViewObj* vobj = (JViewObj*)e.key;
      if (viewSet.indexOf(*vobj) >= 0)
        ((JViewObj*)e.key)->dataNotify(e, (void*)e.modifiers);
      return true;
    }
    case JEvent::AUX_NOTIFY: {
      if (!e.key) return true;
      JViewObj* vobj = (JViewObj*)e.key;
      if (viewSet.indexOf(*vobj) >= 0)
        ((JViewObj*)e.key)->auxNotify(e, (void*)e.modifiers);
      return true;
    }
    case JEvent::GLOBAL_KEY_ACTION:
    case JEvent::GLOBAL_KEY_PRESS:
    case JEvent::GLOBAL_KEY_RELEASE:
    case JEvent::GLOBAL_MOUSE_MOVE:
    case JEvent::GLOBAL_MOUSE_DOWN:
    case JEvent::GLOBAL_MOUSE_ACTION:
    case JEvent::GLOBAL_MOUSE_UP:
    case JEvent::MIXER_LINE_NOTIFY:
    case JEvent::MIXER_CONTROL_NOTIFY:
      viewSet.handleJEvent(e);
      return true;
    case JEvent::GOT_FOCUS: {
      beforePaint();
      focusOn = true;
      viewSet.handleJEvent(e);
      afterPaint();
      return true;
    }
    case JEvent::LOST_FOCUS:
      beforePaint();
      focusOn = false;
      viewSet.handleJEvent(e);
      afterPaint();
      return true;
    case JEvent::KEY_PRESS:
    case JEvent::KEY_ACTION:
    case JEvent::KEY_RELEASE:
      if (currentEdit)
        currentEdit->handleJEvent(e);
      break;
  }
  return JCanvas::handleJEvent(e);
}

boolean JView::action(JEvent& e, JObject* arg) {
  if (!e.target) return true;
  if (e.target == vScroller) {
    int delta = iby-e.key;
    updateInvalidArea();
    beforePaint();
    by = ItoF(iby = e.key);
    calculateJRegion();
    ScrollWindow(0, 0, width, height, 0, delta);
    afterPaint();
    if (vRuler) vRuler->setValue(iby);
    hScroller->repaint();
    vScroller->repaint();
  } else if (e.target == hScroller) {
    int delta = ibx-e.key;
    updateInvalidArea();
    beforePaint();
    bx = ItoF(ibx = e.key);
    calculateJRegion();
    ScrollWindow(0, 0, width, height, delta, 0);
    afterPaint();
    if (hRuler) hRuler->setValue(ibx);
    hScroller->repaint();
    vScroller->repaint();
  } else if (e.target == sScroller) {
    setScale(ztos(zoom=e.key), true);
  } else if (e.target == exit) {
    theMainWindow->dispose();
  } else if (e.target == about) {
    JAbout::create();
  } else if (e.target == group) {
    CM_Group();
  } else if (e.target == ungroup) {
    CM_Ungroup();
  } else if (e.target == loadModule) {
    CM_LoadModule();
  } else if (e.target == noZoom) {
    setScale(ztos(zoom=0) , true);
  } else if (e.target == zoomIn) {
    setScale(ztos(++zoom) , true);
  } else if (e.target == zoomOut) {
    setScale(ztos(--zoom), true);
  } else if (e.target == zoomIn2) {
    setScale(ztos(zoom+=10) , true);
  } else if (e.target == zoomOut2) {
    setScale(ztos(zoom-=10), true);
  } else if (e.target == edit) {
    CM_EditEnabled(e.key == CONCAVE);
  } else if (e.target == guide) {
    CM_GuideVisible(e.key == CONCAVE);
  } else if (e.target == link) {
    CM_LinkVisible(e.key == CONCAVE);
  } else if (e.target == dash) {
    CM_HiddenVisible(e.key == CONCAVE);
  } else if (e.target == ruler) {
    CM_RulerVisible(e.key == CONCAVE);
  } else if (e.target == scaler) {
    CM_ScalerVisible(e.key == CONCAVE);
  } else if (e.target == grid) {
    CM_GridVisible(e.key == CONCAVE);
  } else if (e.target == cut) {
    CM_Cut();
  } else if (e.target == copy) {
    CM_Copy();
  } else if (e.target == paste) {
    CM_Paste();
  } else if (e.target == toFront) {
    CM_ToFront();
  } else if (e.target == toBack) {
    CM_ToBack();
  } else if (e.target == newFile) {
    CM_NewFile();
  } else if (e.target == openFile) {
    CM_OpenFile();
  } else if (e.target == saveFile) {
    CM_SaveFile();
  } else if (e.target == saveAs) {
    CM_SaveAs();
  } else if (e.target == importb) {
    CM_Import();
  } else if (e.target == exportb) {
    CM_Export();
  } else {
    int i;
    int mode = (e.key == CONCAVE);
    for (i=0; i<nToolBox; i++) {
      if (e.target == tbBtn[i]) {
        tbBtn[i]->setBState(mode);
        createToolBox(i);
        return true;
      }
    }
    for (i=0; i<nModuleBox; i++) {
      if (e.target == mbBtn[i]) {
        mbBtn[i]->setBState(mode);
        createModuleBox(i);
        return true;
      }
    }
    if (e.arg && edit->getBState() && !userMode) {
      JModuleButton *btn = (JModuleButton*)e.target;
      if (arg == btn->pmodule) {
        beforePaint();
        JViewObj *last = ((JModuleObj*)arg)->duplicate(&viewSet, null);
        last->reshape(cx, cy, 1.0/scale, 1.0/scale);
        viewSet.calculateExtent();
        focusSet.delAll();
        focusSet.add(*last);
        focusSet.calculateExtent();
        calculateJRegion();
        focusSet.startup();
        repaint(getIExtent(*last));
        afterPaint();
      }
    }
  }
  return true;
}

boolean JView::peerNotify(JEvent& e, JObject* arg) {
  if (!e.target) return true;
  int i;
  for (i=0; i<nToolBox; i++) {
    if (e.target == tBox[i]) {
      tbBtn[i]->setBState(false);
      tbExt[i] = *tBox[i];
      tool->add(*tbPanel[i]);
      tbPanel[i]->width = tbBtn[i]->preferredSize().width;
      if (theMainWindow) theMainWindow->layout();
      tBox[i] = null;
      return true;
    }
  }
  for (i=0; i<nModuleBox; i++) {
    if (e.target == mBox[i]) {
      mbBtn[i]->setBState(false);
      mbExt[i] = *mBox[i];
      mBox[i] = null;
      return true;
    }
  }
  return false;
}

boolean JView::childNotify(JEvent& e, JObject* arg) {
  switch (e.key) {
    case JModuleObj::DIRECT_MODE: {
      JPObject pobj(e.target);
      waiting.lock();
      if (!waitingHash[pobj]) {
        waitingHash.add(pobj);
        waitingArray.append(pobj);
      }
      waiting.unlock();
      idleRequest(0);
      break;
    }
    case JModuleObj::REGION_MODE:
      calculateJRegion();
    case JModuleObj::REPAINT_MODE: {
      JRect rect = getIExtent(*(JFRect*)arg) & 
        (JRect)((JModuleObj*)e.target)->getJRegion();
      if (arg) repaint(rect);
      break;
    }
    case JModuleObj::REQUEST_MODE:
      setCurrentEdit((JModuleObj*)e.target);
      break;
    case JModuleObj::EXTENT_MODE:
      *(JRect*)arg = ((JModuleObj*)e.target)->
        getIExtent(-bx, -by, dscale);
      break;
    case JModuleObj::JPOINT_MODE:
      *(JPoint*)arg = ((JModuleObj*)e.target)->
        getIPoint(*(JFPoint*)e.arg, -bx, -by, dscale);
      break;
    case JModuleObj::EXECUTE_MODE: {
      if (e.modifiers) if (!CM_SaveFile()) break;
      executeFile = *(JString*)arg;
      break;
    }
  }
  return true;
}

boolean JView::closeQuery(JEvent& e) 
{ return checkSave();}

int JView::FtoI(double v) { return (int)JMath::round(v*dscale);}
double JView::ItoF(int v) { return rscale*v;}
double JView::getScale() { return scale;}

boolean JView::setScale(double _scale, boolean frepaint) {
  if (scale == _scale) return false;
  beforePaint();
  scale = _scale;
  zoom = stoz(scale);
  dscale = scale*dpi;
  rscale = 1.0/dscale;
  delta = 0.5*rscale;
  ixmin = FtoI(xmin);
  iymin = FtoI(ymin);
  ixmax = FtoI(xmax)+1;
  iymax = FtoI(ymax)+1;
  icx = FtoI(cx);
  icy = FtoI(cy);
  if (frepaint) {
    bx = max(ItoF(icx-width/2), xmin);
    by = max(ItoF(icy-height/2), ymin);
  }
  ibx = FtoI(bx);
  iby = FtoI(by);
  hScroller->setValue(ibx, width, ixmin, ixmax, true);
  vScroller->setValue(iby, height, iymin, iymax, true);
  bx = ItoF(ibx = hScroller->getValue());
  by = ItoF(iby = vScroller->getValue());
  hRuler->setValue(ibx, width, ixmin, ixmax, dpi, scale, true);
  vRuler->setValue(iby, height, iymin, iymax, dpi, scale, true);
  zValue->setText(JInteger::toJString((int)(scale*100.0))+"%");
  sScroller->setValue(zoom);
  calculateJRegion();
  if (frepaint) repaint();
  afterPaint();
  return true;
}

boolean JView::setView(JFPoint fpt, boolean frepaint) {
  if ((fpt.x == bx) && (fpt.y == by)) return false;
  beforePaint();
  bx = fpt.x;
  by = fpt.y;
  setXYValue(fpt.x, fpt.y);
  ibx = FtoI(bx);
  iby = FtoI(by);
  hScroller->setValue(ibx);
  vScroller->setValue(iby);
  bx = ItoF(ibx = hScroller->getValue());
  by = ItoF(iby = vScroller->getValue());
  hRuler->setValue(ibx);
  vRuler->setValue(iby);
  calculateJRegion();
  if (frepaint) repaint();
  afterPaint();
  return true;
}

boolean JView::setXYValue(double _x, double _y) {
  _x = adjust(_x, xmin, xmax);
  _y = adjust(_y, ymin, ymax);
  beforePaint();
  icx = FtoI(cx = _x);
  xValue->setText(JDouble::toJStringF(cx));
  icy = FtoI(cy = _y);
  yValue->setText(JDouble::toJStringF(cy));
  afterPaint();
  return true;
}

JRect JView::getIExtent(JFRect ext) {
  int ix = FtoI(ext.x)-ibx;
  int iy = FtoI(ext.y)-iby;
  int iw = FtoI(ext.x+ext.width)-ibx-ix+1;
  int ih = FtoI(ext.y+ext.height)-iby-iy+1;
  return JRect(ix, iy, iw, ih);
}

JFRect JView::getFExtent(JRect ext) {
  double x = ItoF(ext.x+ibx)-delta;
  double y = ItoF(ext.y+iby)-delta;
  double w = ItoF(ext.x+ext.width+ibx)-x+delta;
  double h = ItoF(ext.y+ext.height+iby)-y+delta;
  return JFRect(x, y, w, h);
}

JRect JView::getSnapJRect(int x, int y) {
  int guideSnapDist2 = guideSnapDist+guideSnapDist;
  return JRect(x-guideSnapDist, y-guideSnapDist, 
    guideSnapDist2, guideSnapDist2);
}

JFRect JView::getSnapJFRect(double x, double y) {
  double FguideSnapDist = ItoF(guideSnapDist);
  double FguideSnapDist2 = FguideSnapDist+FguideSnapDist;
  return JFRect(x-FguideSnapDist, y-FguideSnapDist, 
    FguideSnapDist2, FguideSnapDist2);
}

boolean JView::snapGuideX(double& x, double& dx) {
  if (snapGridX(x, dx)) return true;
  if (guide->getBState()) {
    JFRect frect = getSnapJFRect(x, 0);
    JViewObj *vobj = vGuideSet.nearestTouch(frect);
    if (vobj) {
      dx = vobj->x-x;
      x = vobj->x;
      return true;
    }
  }
  return false;
}

boolean JView::snapGuideY(double& y, double& dy) {
  if (snapGridX(y, dy)) return true;
  if (guide->getBState()) {
    JFRect frect = getSnapJFRect(0, y);
    JViewObj *hobj = hGuideSet.nearestTouch(frect);
    if (hobj) {
      dy = hobj->y-y;
      y = hobj->y;
      return true;
    }
  }
  return false;
}

boolean JView::snapGuideXY(double& x, double& y, double& dx, double& dy) {
  if (snapGridXY(x, y, dx, dy)) return true;
  if (guide->getBState()) {
    JFRect frect = getSnapJFRect(x, y);
    JViewObj *hobj = hGuideSet.nearestTouch(frect);
    JViewObj *vobj = vGuideSet.nearestTouch(frect);
    if (hobj || vobj) {
      dx = dy = 0.0;
      if (vobj) {
        dx = vobj->x-x;
        x = vobj->x;
      }
      if (hobj) {
        dy = hobj->y-y;
        y = hobj->y;
      }
      return true;
    }
  }
  return false;
}

boolean JView::snapGuideX(double& x1, double& x2, double& dx) {
  if (guide->getBState() || grid->getBState()) {
    double dx1, dx2;
    boolean snap1 = snapGuideX(x1, dx1);
    boolean snap2 = snapGuideX(x2, dx2);
    if (snap1 && snap2)
      dx = (jabs(dx1) < jabs(dx2)) ? dx1 : dx2;
    else if (snap1) dx = dx1;
    else if (snap2) dx = dx2;
    return snap1 || snap2;
  }
  return false;
}

boolean JView::snapGuideY(double& y1, double& y2, double& dy) {
  if (guide->getBState() || grid->getBState()) {
    double dy1, dy2;
    boolean snap1 = snapGuideY(y1, dy1);
    boolean snap2 = snapGuideY(y2, dy2);
    if (snap1 && snap2)
      dy = (jabs(dy1) < jabs(dy2)) ? dy1 : dy2;
    else if (snap1) dy = dy1;
    else if (snap2) dy = dy2;
    return snap1 || snap2;
  }
  return false;
}

boolean JView::snapGridX(double& x, double& dx) {
  if (grid->getBState()) {
    double rx = hRuler->getDelta();
    double kx = JMath::round(x/rx)*rx;
    if (jabs(kx-x) < rx/3) {
      dx = kx-x;
      x = kx;
      return true;
    }
  }
  return false;
}

boolean JView::snapGridY(double& y, double& dy) {
  if (grid->getBState()) {
    double ry = vRuler->getDelta();
    double ky = JMath::round(y/ry)*ry;
    if (jabs(ky-y) < ry/3) {
      dy = ky-y;
      y = ky;
      return true;
    }
  }
  return false;
}

boolean JView::snapGridXY(double& x, double& y, double& dx, double& dy) {
  if (grid->getBState()) {
    dx = dy = 0.0;
    boolean snapAlready = false;
    double rx = hRuler->getDelta();
    double kx = JMath::round(x/rx)*rx;
    double ry = vRuler->getDelta();
    double ky = JMath::round(y/ry)*ry;
    if (jabs(kx-x) < rx/3) {
      dx = kx-x;
      x = kx;
      snapAlready = true;
    }
    if (jabs(ky-y) < ry/3) {
      dy = ky-y;
      y = ky;
      snapAlready = true;
    }
    if (snapAlready) return true;
  }
  return false;
}

boolean JView::typeMatch(int type1, int type2) {
  return (type1 == type2) || 
    (type1 == JDataType::last) ||
    (type2 == JDataType::last);
}

void JView::setCurrentEdit(JModuleObj* newEdit) {
  if (newEdit != currentEdit) {
    if (newEdit) {
      JEvent ev(newEdit, JEvent::GOT_FOCUS, currentEdit);
      if (newEdit->gotEditFocus(ev)) {
        if (currentEdit) {
          JEvent ev(currentEdit, JEvent::LOST_FOCUS, newEdit);
          currentEdit->lostEditFocus(ev);
        }
        currentEdit = newEdit;
      } else setCurrentEdit();
    } else {
      if (currentEdit) {
        JEvent ev(currentEdit, JEvent::LOST_FOCUS, newEdit);
        currentEdit->lostEditFocus(ev);
      }
      currentEdit = newEdit;
    }
  }
}
