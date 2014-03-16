#include "JFlowLayout.h"
#include "JPObject.h"
#include "JInsets.h"

char* theJFlowLayout = JFlowLayout().Register();
const char* JFlowLayout::className() const { return "JFlowLayout";}
JObject* JFlowLayout::clone() const { return new JFlowLayout(*this);}

JDimension JFlowLayout::preferredLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  JInsets insets = parent.insets();
  JArray item = parent.getChildren();
  int nmembers = item.size();
  int dx = insets.left+insets.right;
  int maxwidth = parent.width-dx;
  int x = 0, y = insets.top;
  int rowh = 0;
  JDimension dim(x, y);
  if (maxwidth <= 1) maxwidth = 0x7FFF;
  for (int i=0; i<nmembers; i++) {
    JComponent *m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      JDimension d = m->preferredSize();
      if ((x==0) || ((x+d.width+hgap) <= maxwidth)) {
        if (x > 0) x += hgap;
        if ((align == JUSTIFY) && (i == nmembers-1))
	  d.width=maxwidth-x;
	x += d.width;
	rowh = max(rowh, d.height);
      } else {
        if (align == JUSTIFY) break;
        x = d.width;
        y += vgap+rowh;
	rowh = d.height;
      }
      dim.width = max(dim.width, x);
      dim.height = max(dim.height, y+rowh);
    }
  }
  dim.width += dx;
  dim.height += insets.bottom;
  return dim;
}

JDimension JFlowLayout::minimumLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  JInsets insets = parent.insets();
  JArray item = parent.getChildren();
  int nmembers = item.size();
  int dx = insets.left+insets.right;
  int maxwidth = parent.width-dx;
  int x = 0, y = insets.top;
  int rowh = 0;
  JDimension dim(x, y);
  if (maxwidth <= 1) maxwidth = 0x7FFF;
  for (int i=0; i<nmembers; i++) {
    JComponent *m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      JDimension d = m->minimumSize();
      if ((x==0) || ((x+d.width+hgap) <= maxwidth)) {
        if (x > 0) x += hgap;
        if ((align == JUSTIFY) && (i == nmembers-1))
	  d.width=maxwidth-x;
	x += d.width;
	rowh = max(rowh, d.height);
      } else {
        if (align == JUSTIFY) break;
        x = d.width;
        y += vgap+rowh;
	rowh = d.height;
      }
      dim.width = max(dim.width, x);
      dim.height = max(dim.height, y+rowh);
    }
  }
  dim.width += dx;
  dim.height += insets.bottom;
  return dim;
}

void JFlowLayout::moveComponents(JArray& item, 
  int x, int y, int width, int height, int rowStart, int rowEnd) {
  switch (align) {
    case JUSTIFY:
    case LEFT:
      break;
    case CENTER:
      x += width/2;
      break;
    case RIGHT:
      x += width;
      break;
  }
  for (int i=rowStart; i<rowEnd; i++) {
    JComponent *m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      m->move(x, y + (height-m->height) / 2);
      x += hgap + m->width;
    }
  }
}

void JFlowLayout::layout(JComponent& parent) {
  JInsets insets;
  if (parent.isVisible()) insets = parent.insets();
  JArray item = parent.getChildren();
  int nmembers = item.size();
  int maxwidth = parent.width-(insets.left+insets.right);
  int x = 0, y = insets.top;
  int rowh = 0, start = 0;
  for (int i=0; i<nmembers; i++) {
    JComponent *m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      JDimension d = m->preferredSize();
      m->resize(d.width, d.height);
      if ((x==0) || ((x+d.width+hgap) <= maxwidth)) {
        if (x > 0) x += hgap;
        if ((align == JUSTIFY) && (i == nmembers-1))
	  m->resize(d.width=maxwidth-x, d.height);
	x += d.width;
	rowh = max(rowh, d.height);
      } else {
	moveComponents(item, insets.left, y, maxwidth-x, rowh, start, i);
        if (align == JUSTIFY) break;
        x = d.width;
        y += vgap+rowh;
	rowh = d.height;
	start = i;
      }
    }
  }
  moveComponents(item, insets.left, y, maxwidth-x, rowh, start, nmembers);
}

JFlowLayout::JFlowLayout() {
  align = CENTER;
  hgap = vgap = 0;
}

JFlowLayout::JFlowLayout(int _align) {
  align = _align;
  hgap = vgap = 0;
}

JFlowLayout::JFlowLayout(int _align, int _hgap, int _vgap) {
  align = _align;
  hgap = _hgap;
  vgap = _vgap;
}

