#include "JView.h"
#include "JDialog.h"
#include "JPanel.h"
#include "JBorderLayout.h"
#include "JFlowLayout.h"
#include "JScrambledStringProperty.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JColorProperty.h"
#include "JPropertyBox.h"
#include "JModuleButton.h"

#define maxModuleBox 8
#define maxToolBox 2

int JView::hashSize = 101;
int JView::nModuleBox = maxModuleBox;
enum { DIGITAL, MATH, KEYBOARD, MULTIMEDIA, DISPLAY, IO, MISC, EXTERNAL};
JRect JView::mbDefault(0x89, 0x5F, 0x6F, 0x122);
JRect JView::mbExt[maxModuleBox];
char* JView::mbTag[maxModuleBox] =
  { "DL", "MA", "KB", "MM", "DS", "IO", "MI", "EM"};
char* JView::mbTitle[maxModuleBox] = { 
  "Digital Logic", "Math", "Keyboard", "MultiMedia", 
  "Display", "I/O", "Misc", "External"};
JCanvas* JView::mbBtn[maxModuleBox] = 
  { null, null, null, null, null, null, null, null};
JComponent* JView::mBox[maxModuleBox] = 
  { null, null, null, null, null, null, null, null};

int JView::nToolBox = maxToolBox;
enum { DESKTOP, TOOL};
JCanvas* JView::tbPanel[maxToolBox];
JCanvas* JView::tbCanvas[maxToolBox];
JRect JView::tbDefault(0x89, 0x5F, 62, 254);
JRect JView::tbExt[maxToolBox];
char* JView::tbTag[maxToolBox] = { "DT", "TL"};
char* JView::tbTitle[maxToolBox] = {"Desktop", "Tool"};
JCanvas* JView::tbBtn[maxToolBox] = { null, null};
JComponent* JView::tBox[maxToolBox] = { null, null};

void JView::createToolBox(int n) {
  if (tbBtn[n]->getBState()) {
    if (!tBox[n]) {
      JComponent *pBox = tBox[n] = JDialog::create(false);
      tbCanvas[n] = JCanvas::create(pBox);
      JPanel *panel = JPanel::create(pBox, tbCanvas[n]);
      JBorderLayout border;
      tbCanvas[n]->setJInsets(JInsets(2, 2, 2, 2));
      tbCanvas[n]->setLayout(border);
      tbCanvas[n]->add(JBorderLayout::CENTER, *tbPanel[n]);
      pBox->setBackground(JColor::lightGray);
      pBox->setLayout(border);
      pBox->add(JBorderLayout::CENTER, *panel);
      pBox->setText(tbTitle[n]);
      tBox[n]->reshape(tbExt[n]);
    } else {
      tbCanvas[n]->add(JBorderLayout::CENTER, *tbPanel[n]);
      tbCanvas[n]->layout();
    }
    tBox[n]->show(!userMode);
  } else if (tBox[n]) {
    tool->add(*tbPanel[n]);
    tbPanel[n]->width = tbBtn[n]->preferredSize().width;
    tBox[n]->hide();
  }
  theMainWindow->layout();
}

JArray JView::externalModuleTag;
DllImport extern JDictionary *pClassDict;

JModuleObj* getReference(JString name) 
{ return (JModuleObj*)(*pClassDict)[name.toUpperCase()];}

void JView::addButtons(JComponent* panel, JArray tag) {
  for (int i=0, sz=tag.size(); i<sz; i++) {
    JModuleObj *obj = getReference(*(JString*)tag[i]);
    if (obj) obj->addButton(panel);
    else break;
  }
}

#if !defined(NEAT_LIB)
  DllImport 
#endif
extern char* theJAddObj;
#if !defined(NEAT_LIB)
  DllImport 
#endif
extern char* theJANDObj;


void JView::createModuleBox(int n) {
  if (!mBox[n]) {
    if (!mbBtn[n]->getBState()) return;
    JComponent *pBox = mBox[n] = JDialog::create();
    JCanvas *canvas = JCanvas::create(pBox);
    JPanel *panel = JPanel::create(pBox, canvas);
    JBorderLayout border;
    JFlowLayout tflow(JFlowLayout::LEFT, 2, 2);
    canvas->setJInsets(JInsets(2, 2, 2, 2));
    canvas->setLayout(tflow);
    pBox->setLayout(border);
    pBox->add(JBorderLayout::CENTER, *panel);
    pBox->setText(mbTitle[n]);
    switch (n) {
      case DIGITAL: {
        extern char* theJNOTObj;
        extern char* theJORObj;
        extern char* theJXORObj;
        extern char* theJGreaterThanObj;
        extern char* theJGreaterEqualObj;
        extern char* theJEqualObj;
        extern char* theJNotEqualObj;
        extern char* theJMultiplyObj;
        extern char* theJSubtractObj;
        extern char* theJDivideObj;
        extern char* theJPowObj;
        extern char* theJAbsObj;
        extern char* theJMaxObj;
        extern char* theJMinObj;
        extern char* theJRemainObj;
        extern char* theJRandomObj;
        extern char* theJControlObj;
        extern char* theJSampleObj;
        extern char* theJPulseObj;
        extern char* theJDelayObj;
        extern char* theJAccumulatorObj;
        extern char* theJMultiplexerObj;
        extern char* theJDeMultiplexerObj;
        extern char* theJEncoderObj;
        extern char* theJDecoderObj;
        extern char* theJExclusiveObj;
        extern char* theJClockDividerObj;
        extern char* theJTimeObj;
        extern char* theJTimerObj;
        extern char* theJHPCounterObj;
        extern char* theJCalibrateObj;
        extern char* theJAvgFilterObj;
        extern char* theJDelaySustainObj;
        extern char* theJStateObj;
#if defined BENCHMARK
        extern char* theJBenchmarkObj;
#endif
        char* tag[] = {
	  theJNOTObj, theJANDObj, theJORObj, theJXORObj,
	  theJGreaterThanObj, theJGreaterEqualObj,
	  theJEqualObj, theJNotEqualObj, theJAddObj,
	  theJMultiplyObj, theJSubtractObj, theJDivideObj,
          theJAbsObj, theJPowObj,
	  theJMaxObj, theJMinObj,
	  theJRemainObj, theJRandomObj,
          theJControlObj, theJSampleObj,
 	  theJPulseObj, theJDelayObj, 
          theJAccumulatorObj, theJMultiplexerObj,
	  theJDeMultiplexerObj, theJEncoderObj, theJDecoderObj,
	  theJExclusiveObj, theJClockDividerObj, theJTimeObj,
	  theJTimerObj, theJHPCounterObj, theJCalibrateObj, 
	  theJAvgFilterObj, theJDelaySustainObj, theJStateObj, 
#if defined BENCHMARK
          theJBenchmarkObj,
#endif
	  null
        };
        addButtons(canvas, tag);
        break;
      }
      case MATH: {
        extern char* theJCEqualObj;
        extern char* theJCNotEqualObj;
        extern char* theJCAddObj;
        extern char* theJCSubtractObj;
        extern char* theJCMultiplyObj;
        extern char* theJCDivideObj;
        extern char* theJCtoRObj;
        extern char* theJRtoCObj;
        extern char* theJCPolrObj;
        extern char* theJPolrCObj;
	extern char* theJCSinObj;
	extern char* theJCSinhObj;
	extern char* theJCCosObj;
	extern char* theJCCoshObj;
	extern char* theJCTanObj;
	extern char* theJCTanhObj;
	extern char* theJCExpObj;
	extern char* theJCConjObj;
        extern char* theJRGreaterThanObj;
        extern char* theJRGreaterEqualObj;
        extern char* theJREqualObj;
        extern char* theJRNotEqualObj;
        extern char* theJRAddObj;
        extern char* theJRMultiplyObj;
        extern char* theJRSubtractObj;
        extern char* theJRDivideObj;
        extern char* theJRAbsObj;
        extern char* theJRPowObj;
        extern char* theJRMaxObj;
        extern char* theJRMinObj;
        extern char* theJRSinObj;
        extern char* theJRCosObj;
        extern char* theJRASinObj;
        extern char* theJRACosObj;
        extern char* theJRTanObj;
        extern char* theJRATanObj;
        extern char* theJRExpObj;
        extern char* theJRLogObj;
        extern char* theJRSqrtObj;
        extern char* theJRRoundObj;
        extern char* theJRCeilObj;
        extern char* theJRFloorObj;
        extern char* theJRModObj;
        extern char* theJRAtan2Obj;
        extern char* theJRPIObj;
        extern char* theJREObj;
        extern char* theJRRandomObj;
        extern char* theJRDelayObj;
        extern char* theJRCalibrateObj;
        char* tag[] = {
          theJCEqualObj, theJCNotEqualObj,
          theJCAddObj, theJCSubtractObj,
	  theJCMultiplyObj, theJCDivideObj,
	  theJCtoRObj, theJRtoCObj,
	  theJCPolrObj, theJPolrCObj,
	  theJCSinObj, theJCSinhObj,
	  theJCCosObj, theJCCoshObj,
	  theJCTanObj, theJCTanhObj,
	  theJCExpObj, theJCConjObj,
	  theJRGreaterThanObj, 
          theJRGreaterEqualObj, theJREqualObj, theJRNotEqualObj,
          theJRAddObj, theJRMultiplyObj, theJRSubtractObj,
          theJRDivideObj, theJRAbsObj, theJRPowObj,
          theJRMaxObj, theJRMinObj, theJRSinObj,
          theJRCosObj, theJRASinObj, theJRACosObj,
          theJRTanObj, theJRATanObj, theJRExpObj,
          theJRLogObj, theJRSqrtObj, theJRRoundObj,
          theJRCeilObj, theJRFloorObj, theJRModObj,
          theJRAtan2Obj, theJRPIObj, theJREObj,
          theJRRandomObj, theJRDelayObj, theJRCalibrateObj,
	  null
        };
        addButtons(canvas, tag);
        break;
      }
      case KEYBOARD: {
        extern char* theJSKeyboardObj;
        extern char* theJKeyboardObj;
        char* tag[] = {theJSKeyboardObj, 
          theJKeyboardObj, null};
        addButtons(canvas, tag);
        break;
      }
      case MULTIMEDIA: {
        extern char* theJMixerObj;
        extern char* theJMIDIOutObj;
        extern char* theJMIDIInObj;
        extern char* theJMIDIObj;
        extern char* theJMIDIChannelObj;
        extern char* theJMIDIFileObj;
        extern char* theJRMIDFileObj;
        extern char* theJWaveInObj;
        extern char* theJWaveOutObj;
        extern char* theJWaveFileObj;
        extern char* theJAudioCodecObj;
        char* tag[] = {
	  theJMixerObj, theJMIDIOutObj, theJMIDIInObj,
	  theJMIDIObj, theJMIDIChannelObj, theJMIDIFileObj,
	  theJRMIDFileObj, theJWaveInObj, theJWaveOutObj,
	  theJWaveFileObj, theJAudioCodecObj, null};
        addButtons(canvas, tag);
        break;
      }
      case DISPLAY: {
        extern char* theJColorObj;
        extern char* theJLabelObj;
        extern char* theJIntegerObj;
        extern char* theJRealObj;
        extern char* theJRealComplexObj;
        extern char* theJDateObj;
		extern char* theJBytesObj;
        extern char* theJBtnObj;
        extern char* theJPushBtnObj;
        extern char* theJSwitchObj;
        extern char* theJFocusObj;
        extern char* theJLEDObj;
        extern char* theJ1DViewerObj;
        extern char* theJ1DMeterObj;
        extern char* theJ1DSliderObj;
        extern char* theJ2DMeterObj;
        extern char* theJ2DSliderObj;
        char* tag[] = {
	  theJColorObj, theJLabelObj, 
          theJIntegerObj, theJRealObj, theJRealComplexObj,
          theJDateObj, theJBytesObj, theJBtnObj, theJPushBtnObj, 
          theJSwitchObj, theJFocusObj, theJLEDObj, 
          theJ1DViewerObj, theJ1DMeterObj, theJ1DSliderObj, 
          theJ2DMeterObj, theJ2DSliderObj, null};
        addButtons(canvas, tag);
        break;
      }
      case IO: {
        extern char* theJNodeObj;
        extern char* theJComplexObj;
        extern char* theJNTLFileObj;
        extern char* theJEXEFileObj;
        extern char* theJDataBaseObj;
        extern char* theJMouseObj;
        extern char* theJMousePosObj;
        extern char* theJMouseBtnObj;
        extern char* theJConvertObj;
        extern char* theJRecorderObj;
        extern char* theJTailObj;
        extern char* theJSocketObj;
        extern char* theJServerSocketObj;
        extern char* theJJoyStickObj;
        extern char* theJLPTObj;
        extern char* theJCOMObj;
        extern char* theJCHObj;
        extern char* theJTNGObj;
        extern char* theJTNG3Obj;
		extern char* theJTNG3XObj;
        extern char* theJTNG4Obj;
        extern char* theJOxfordObj;
        extern char* theJDaviconObj;
        char* tag[] = {
	  theJComplexObj, theJNodeObj, 
          theJNTLFileObj, theJEXEFileObj, theJDataBaseObj,
          theJMouseObj, theJMousePosObj, theJMouseBtnObj, 
	  theJConvertObj, theJRecorderObj, theJTailObj, theJSocketObj,
	  theJServerSocketObj, theJJoyStickObj, theJLPTObj,
	  theJCOMObj, /*theJCHObj, */
          theJTNGObj, theJTNG3Obj, theJTNG3XObj, theJTNG4Obj,
	  theJOxfordObj, theJDaviconObj, null};
        addButtons(canvas, tag);
        break;
      }
      case MISC: {
        extern char* theJBtoIObj;
        extern char* theJItoBObj;
        extern char* theJWtoIObj;
        extern char* theJItoWObj;
        extern char* theJRtoIObj;
        extern char* theJItoRObj;
        extern char* theJStoIObj;
        extern char* theJItoSObj;
        extern char* theJStoBObj;
        extern char* theJBtoSObj;
        extern char* theJDtoRObj;
        extern char* theJRtoDObj;
        extern char* theJDGreaterThanObj;
        extern char* theJDGreaterEqualObj;
        extern char* theJDEqualObj;
        extern char* theJDNotEqualObj;
        extern char* theJSGreaterThanObj;
        extern char* theJSGreaterEqualObj;
        extern char* theJSEqualObj;
        extern char* theJSNotEqualObj;
        extern char* theJSAddObj;
        extern char* theJSSubObj;
        extern char* theJSDelObj;
        extern char* theJSInsObj;
        extern char* theJSLenObj;
        extern char* theJSPosObj;
        extern char* theJSUpperObj;
        extern char* theJSLowerObj;
        extern char* theJBAddObj;
        extern char* theJBSubObj;
        extern char* theJBDelObj;
        extern char* theJBInsObj;
        extern char* theJBLenObj;
        extern char* theJBPosObj;
        char* tag[] = {
          theJRtoIObj, theJItoRObj, 
          theJBtoIObj, theJItoBObj,
          theJWtoIObj, theJItoWObj,
          theJStoIObj, theJItoSObj,
          theJStoBObj, theJBtoSObj,
          theJDtoRObj, theJRtoDObj,
          theJDGreaterThanObj,
          theJDGreaterEqualObj,
          theJDEqualObj,
          theJDNotEqualObj,
          theJSGreaterThanObj,
          theJSGreaterEqualObj,
          theJSEqualObj,
          theJSNotEqualObj,
          theJSAddObj, theJSSubObj,
          theJSDelObj, theJSInsObj,
          theJSLenObj, theJSPosObj,
          theJSUpperObj, theJSLowerObj,
          theJBAddObj, theJBSubObj,
          theJBDelObj, theJBInsObj,
          theJBLenObj, theJBPosObj,
	  null};
        addButtons(canvas, tag);
        break;
      }
      case EXTERNAL: {
        addButtons(canvas, externalModuleTag);
        break;
      }
    }
    mBox[n]->reshape(mbExt[n]);
  }
  mBox[n]->show(mbBtn[n]->getBState() && !userMode);
}

char* guideStyleTag[] = {"Dashed", "Solid", null};

JArray JView::getProperties() { 
  JArray properties;
  int recentFilesSelect = 0;
  properties.append(JIntegerListProperty("recentFilesSelect", recentFilesSelect, 
    recentFiles));
  properties.append(JIntegerProperty("maxRecentFiles", maxRecentFiles, 4, 20));
  properties.append(JScrambledStringProperty("userModePassword", userModePassword));
  properties.append(JIntegerListProperty("editEnabled", 
    edit->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("guideVisible", 
    guide->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JColorProperty("guideColor", guideColor));
  properties.append(JIntegerListProperty("guideStyle", guideStyle, guideStyleTag));
  properties.append(JIntegerProperty("guideSnapDist", guideSnapDist, 3, 8));
  properties.append(JIntegerListProperty("linkVisible", 
    link->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JColorProperty("linkColor", linkColor));
  properties.append(JIntegerListProperty("hiddenVisible", 
    dash->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("rulerVisible", 
    ruler->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JColorProperty("gridColor", gridColor));
  properties.append(JIntegerListProperty("gridVisible", 
    grid->getBState(), JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("userMode", userMode, 
    JIntegerListProperty::booleanTag));
  properties.append(JIntegerListProperty("withCaption", withCaption, 
    JIntegerListProperty::booleanTag));
  properties.append(JColorProperty("frameColor", frameColor));
  properties.append(JColorProperty("backgroundColor", backgroundColor));
  return properties;
}

void JView::updateRecentFiles(JString name) {
  int sz = recentFiles.size();
  for (int i=0; i<sz; i++) {
    if (name == *(JString*)recentFiles[i]) {
      if (i > 0) {
        recentFiles.del(i);
        recentFiles.insert(name);
      }
      if (sz > maxRecentFiles)
        recentFiles.setSize(maxRecentFiles);
      return;
    }
  }
  recentFiles.insert(name);
  if (sz+1 > maxRecentFiles)
    recentFiles.setSize(maxRecentFiles);
}

boolean JView::updateProperty(JProperty& prop) { 
  if (prop.getName() == JString("recentFilesSelect")) {
    if (!checkSave()) return true;
    JString name = *(JString*)recentFiles[((JIntegerListProperty*)&prop)->value];
    if (readFile(name) && (importMode == NTL_MODE))
      putFileName(name);
    return true;
  } else if (prop.getName() == JString("maxRecentFiles")) {
    maxRecentFiles = ((JIntegerListProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("userModePassword")) {
    userModePassword = ((JScrambledStringProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("editEnabled")) {
    return CM_EditEnabled(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("guideVisible")) {
    return CM_GuideVisible(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("guideSnapDist")) {
    beforePaint();
    guideSnapDist = ((JIntegerProperty*)&prop)->value;
    afterPaint();
    return true;
  } else if (prop.getName() == JString("linkVisible")) {
    return CM_LinkVisible(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("hiddenVisible")) {
    return CM_HiddenVisible(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("rulerVisible")) {
    return CM_RulerVisible(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("gridVisible")) {
    return CM_GridVisible(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("userMode")) {
    return CM_UserMode(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("withCaption")) {
    return CM_Caption(((JIntegerListProperty*)&prop)->value);
  } else if (prop.getName() == JString("guideColor")) {
    guideColor = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("guideStyle")) {
    guideStyle = ((JIntegerListProperty*)&prop)->value;
    repaint();
    return true;
  } else if (prop.getName() == JString("linkColor")) {
    linkColor = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("frameColor")) {
    frameColor = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("backgroundColor")) {
    backgroundColor = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  } else if (prop.getName() == JString("gridColor")) {
    gridColor = ((JColorProperty*)&prop)->color;
    repaint();
    return true;
  }
  return false;
}

boolean JView::propertyDialog(int x, int y) {
  int select = 0;
  JArray properties = getProperties();
  if (!properties.size()) return false;
  while (JPropertyBox::create(
    JString("Properties of ")+(className()+1),
    properties, select, x, y) == JMessageBox::OK) {
    JProperty &prop = *(JProperty*)properties[select];
    if (prop.edit(x, y)) {
      updateProperty(prop);
      properties = getProperties();
    }
  }
  return true;
}

boolean JView::mouseEnter(JEvent& e, int x, int y) {
  if (e.target == this) sValue->setText("NeatTools Desktop");
  else if (e.target == edit) sValue->setText("Edit Mode Toggle <Ctrl-E>");
  else if (e.target == guide) sValue->setText("Guide Toggle");
  else if (e.target == link) sValue->setText("Link Toggle");
  else if (e.target == dash) sValue->setText("Hidden Line Toggle");
  else if (e.target == ruler) sValue->setText("Ruler Toggle");
  else if (e.target == scaler) sValue->setText("Scaler Toggle");
  else if (e.target == grid) sValue->setText("Grid Toggle");
  else if (e.target == zoomOut2) sValue->setText("Zoom Out by 2");
  else if (e.target == zoomOut) sValue->setText("Zoom Out");
  else if (e.target == noZoom) sValue->setText("Original Scale");
  else if (e.target == zoomIn) sValue->setText("Zoom In");
  else if (e.target == zoomIn2) sValue->setText("Zoom In by 2");
  else if (e.target == newFile) sValue->setText("New File <Ctrl-N>");
  else if (e.target == openFile) sValue->setText("Open File <Ctrl-O>");
  else if (e.target == saveFile) sValue->setText("Save File <Ctrl-S>");
  else if (e.target == saveAs) sValue->setText("Save File As");
  else if (e.target == importb) sValue->setText("Import Component");
  else if (e.target == exportb) sValue->setText("Export Component");
  else if (e.target == cut) sValue->setText("Cut <Ctrl-X>");
  else if (e.target == copy) sValue->setText("Copy <Ctrl-C>");
  else if (e.target == paste) sValue->setText("Paste <Ctrl-V>");
  else if (e.target == toFront) sValue->setText("To Front");
  else if (e.target == toBack) sValue->setText("To Back");
  else if (e.target == group) sValue->setText("Group");
  else if (e.target == ungroup) sValue->setText("Ungroup");
  else if (e.target == loadModule) sValue->setText("Load External Module");
  else if (e.target == about) sValue->setText("About NeatTools");
  else if (e.target == exit) sValue->setText("Exit NeatTools <Ctrl-Z>");
  else if (e.target == xValue) sValue->setText("X Anchor Position");
  else if (e.target == yValue) sValue->setText("Y Anchor Position");
  else if (e.target == zValue) sValue->setText("Scale Percentage");
  else if (e.target == dValue) sValue->setText("Dirty Status");
  else if (e.target == sValue) sValue->setText("Status");
  else if (e.target == vRuler) sValue->setText("Vertical Ruler");
  else if (e.target == hRuler) sValue->setText("Horizontal Ruler");
  else {
    int i;
    for (i=0; i<nToolBox; i++) {
      if (e.target == tbBtn[i]) {
        sValue->setText(JString(tbTitle[i])+" Toolbar Toggle");
        return true;
      }
    }
    for (i=0; i<nModuleBox; i++) {
      if (e.target == mbBtn[i]) {
        sValue->setText(JString(mbTitle[i])+" Toolbox Toggle");
        return true;
      }
    }
    if (JString(e.target->className()) == 
      JString("JModuleButton")) {
      JModuleButton *btn = (JModuleButton*)e.target;
      sValue->setText(JString(btn->pmodule->className()+1)+" Module");
      return true;
    }
  }
  return true;
}

boolean JView::mouseExit(JEvent& e, int x, int y) {
  sValue->setText("");
  return true;
}

void JView::calculateJRegion() {
  region = JRegion(0, 0, width, height);
  viewSet.calculateJRegion(region, -bx, -by, dscale);
}

void JView::clearProcessArray() {
  currentObj = null;
  currentHit = null;
  waiting.lock();
  waitingArray.Release();
  waitingHash = JHashTable(hashSize);
  waiting.unlock();
  process.lock();
  processArray.Release();
  process.unlock();
}

void JView::clearProcessArrayInFocusSet() {
  int i, sz;
  JArray newArray;
  JHashTable hash(hashSize);
  focusSet.toHash(hash);
  waiting.lock();
  waitingHash = JHashTable(hashSize);
  for (i=0, sz=waitingArray.size(); i<sz; i++) {
    if (!hash[*waitingArray[i]]) {
      newArray.append(*waitingArray[i]);
      waitingHash.add(*waitingArray[i]);
    }
  }
  waitingArray = newArray;
  waiting.unlock();
  newArray.Release();
  process.lock();
  for (i=0, sz=processArray.size(); i<sz; i++) {
    if (!hash[*processArray[i]])
      newArray.append(*processArray[i]);
  }
  processArray = newArray;
  process.unlock();
}
