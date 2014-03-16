#include "JModuleCanvas.h"

char* theJModuleCanvas = JModuleCanvas().Register();
JModuleCanvas* JModuleCanvas::create(JComponent *p, JModuleObj* obj) { 
  JModuleCanvas *dest = (JModuleCanvas*)createJComponent(theJModuleCanvas, p);
  dest->pmodule = obj;
  return dest;
}

const char* JModuleCanvas::className() const { return "JModuleCanvas";}
JObject* JModuleCanvas::clone() const { return new JModuleCanvas(*this);}
JModuleCanvas::JModuleCanvas() 
{ base = 6; ratio = 6; pmodule = null;}

void JModuleCanvas::startup() 
{ setBackground(JColor::lightGray);}

void JModuleCanvas::paint(JGraphics g) {
  if (!width || !pmodule) return;
  JModuleObj *obj = (JModuleObj*)(pmodule->clone());
  JRect rect = g.getClipJRect();
  JRegion rgn(rect);
  g.setJColor(getBackground());
  g.fillJRect(rect);
  obj->height = obj->width*height/width;
  obj->paint(g, -obj->x, -obj->y, 
    rgn, ((double)width)/obj->width);
  obj->reset();
  delete obj;
}

