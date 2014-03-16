#include "JGridLayout.h"
#include "JPObject.h"
#include "JInsets.h"

char* theJGridLayout = JGridLayout().Register();
const char* JGridLayout::className() const { return "JGridLayout";}
JObject* JGridLayout::clone() const { return new JGridLayout(*this);}

JDimension JGridLayout::preferredLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  JInsets insets = parent.insets();
  JArray item = parent.getChildren();
  int w = 0, h = 0;
  int nmembers = item.size();
  int nrows = rows;
  int ncols = cols;
  if (nrows > 0) ncols = (nmembers+nrows-1)/nrows;
  else nrows = (nmembers+ncols-1)/ncols;
  for (int i=0; i<nmembers; i++) {
    JComponent* m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      JDimension d = m->preferredSize();
      if (w < d.width) w = d.width;
      if (h < d.height) h = d.height;
    }
  }
  return JDimension(insets.left+insets.right+ncols*w+(ncols-1)*hgap, 
    insets.top+insets.bottom+nrows*h+(nrows-1)*vgap);
}

JDimension JGridLayout::minimumLayoutSize(JComponent& parent) {
  if (!parent.isVisible()) return JDimension();
  JInsets insets = parent.insets();
  JArray item = parent.getChildren();
  int w = 0, h = 0;
  int nmembers = item.size();
  int nrows = rows;
  int ncols = cols;
  if (nrows > 0) ncols = (nmembers+nrows-1)/nrows;
  else nrows = (nmembers+ncols-1)/ncols;
  for (int i=0; i<nmembers; i++) {
    JComponent* m = (JComponent*)OPTR(item[i]);
    if (m->isVisible()) {
      JDimension d = m->minimumSize();
      if (w < d.width) w = d.width;
      if (h < d.height) h = d.height;
    }
  }
  return JDimension(insets.left+insets.right+ncols*w+(ncols-1)*hgap, 
    insets.top+insets.bottom+nrows*h+(nrows-1)*vgap);
}

void JGridLayout::layout(JComponent& parent) {
  JInsets insets;
  if (parent.isVisible()) insets = parent.insets();
  JArray item = parent.getChildren();
  int nmembers = item.size();
  int w = parent.width-(insets.left+insets.right);
  int h = parent.height-(insets.top+insets.bottom);
  int nrows = rows;
  int ncols = cols;
  if (nrows > 0) ncols = (nmembers+nrows-1)/nrows;
  else nrows = (nmembers+ncols-1)/ncols;
  w = (w-(ncols-1)*hgap)/ncols;
  h = (h-(nrows-1)*vgap)/nrows;
  for (int c=0, x=insets.left; c<ncols; c++, x+=w+hgap) {
    for (int r=0, y=insets.top; r<nrows; r++, y+=h+vgap) {
      int i = r * ncols + c;
      if (i < nmembers) {
        JComponent* m = (JComponent*)OPTR(item[i]);
	m->reshape(x, y, w, h);
      }
    }
  }
}


JGridLayout::JGridLayout() {
  rows = 1;
  cols = 0;
  hgap = vgap = 0;
}

JGridLayout::JGridLayout(int _rows, int _cols) {
  rows = _rows;
  cols = _cols;
  hgap = vgap = 0;
  if (!rows && !cols) {
    rows = 1;
    cols = 0;
  }
}

JGridLayout::JGridLayout(int _rows, int _cols, int _hgap, int _vgap) {
  rows = _rows;
  cols = _cols;
  hgap = _hgap;
  vgap = _vgap;
  if (!rows && !cols) {
    rows = 1;
    cols = 0;
  }
}

