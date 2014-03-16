#include "JBorderLayout.h"
#include "JInsets.h"
	      
char* theJBorderLayout = JBorderLayout().Register();
const char* JBorderLayout::className() const { return "JBorderLayout";}
JObject* JBorderLayout::clone() const { return new JBorderLayout(*this);}

void JBorderLayout::addLayoutComponent(int type, JComponent& comp) {
  if ((type < 0) || (type >= LAST)) return;
  item[type] = &comp;
}

void JBorderLayout::removeLayoutComponent(JComponent& comp) {
  for (int i=0; i<LAST; i++) {
    if (item[i] == &comp) {
      item[i] = null;
      break;
    }
  }
}

JDimension JBorderLayout::preferredLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  int i;
  JDimension dim;
  JInsets insets = parent.insets();
  for (i=EAST; i<=WEST; i++) {
    if (item[i] && item[i]->isVisible()) {
      JDimension d = item[i]->preferredSize();
      if (d.width > 0) dim.width += d.width + hgap;
      dim.height = max(d.height, dim.height);
    } 
  }
  if (item[CENTER] && item[CENTER]->isVisible()) {
    int iw = item[i]->width;
    item[i]->width = parent.width-
      (insets.left+insets.right+dim.width);
    JDimension d = item[i]->preferredSize();
    item[i]->width = iw;
    dim.width += d.width;
    dim.height = max(d.height, dim.height);
  } 
  for (i=NORTH; i<=SOUTH; i++) {
    if (item[i] && item[i]->isVisible()) {
      JDimension d = item[i]->preferredSize();
      dim.width = max(d.width, dim.width);
      if (d.height > 0) dim.height += d.height + vgap;
    } 
  }
  dim.width += insets.left + insets.right;
  dim.height += insets.top + insets.bottom;
  return dim;
}

JDimension JBorderLayout::minimumLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  int i;
  JDimension dim;
  JInsets insets = parent.insets();
  for (i=EAST; i<=WEST; i++) {
    if (item[i] && item[i]->isVisible()) {
      JDimension d = item[i]->minimumSize();
      if (d.width > 0) dim.width += d.width + hgap;
      dim.height = max(d.height, dim.height);
    } 
  }
  if (item[CENTER] && item[CENTER]->isVisible()) {
    int iw = item[i]->width;
    item[i]->width = parent.width-
      (insets.left+insets.right+dim.width);
    JDimension d = item[i]->minimumSize();
    item[i]->width = iw;
    dim.width += d.width;
    dim.height = max(d.height, dim.height);
  } 
  for (i=NORTH; i<=SOUTH; i++) {
    if (item[i] && item[i]->isVisible()) {
      JDimension d = item[i]->minimumSize();
      dim.width = max(d.width, dim.width);
      if (d.height > 0) dim.height += d.height + vgap;
    } 
  }
  dim.width += insets.left + insets.right;
  dim.height += insets.top + insets.bottom;
  return dim;
}

void JBorderLayout::layout(JComponent& parent) {
  JInsets insets;
  if (parent.isVisible()) insets = parent.insets();
  int top = insets.top;
  int bottom = parent.height - insets.bottom;
  int left = insets.left;
  int right = parent.width - insets.right;
  if (item[NORTH] && item[NORTH]->isVisible()) {
    JDimension d = item[NORTH]->preferredSize();
    item[NORTH]->reshape(left, top, right-left, d.height);
    if (d.height > 0) top += d.height+vgap;
  }
  if (item[SOUTH] && item[SOUTH]->isVisible()) {
    JDimension d = item[SOUTH]->preferredSize();
    item[SOUTH]->reshape(left, bottom-d.height, right-left, d.height);
    if (d.height > 0) bottom -= d.height+vgap;
  }
  if (item[EAST] && item[EAST]->isVisible()) {
    JDimension d = item[EAST]->preferredSize();
    item[EAST]->reshape(right-d.width, top, d.width, bottom-top);
    if (d.width > 0) right -= d.width+hgap;
  }
  if (item[WEST] && item[WEST]->isVisible()) {
    JDimension d = item[WEST]->preferredSize();
    item[WEST]->reshape(left, top, d.width, bottom-top);
    if (d.width > 0) left += d.width+hgap;
  }
  if (item[CENTER] && item[CENTER]->isVisible())
    item[CENTER]->reshape(left, top, right-left, bottom-top);
}

JBorderLayout::JBorderLayout() {
  hgap = vgap = 0;
  for (int i=0; i<LAST; item[i++] = null);
}

JBorderLayout::JBorderLayout(int _hgap, int _vgap) {
  hgap = _hgap;
  vgap = _vgap;
  for (int i=0; i<LAST; item[i++] = null);
}

