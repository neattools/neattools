#include "JPanel.h"
#include "JCanvas.h"
#include "JScroller.h"
#include "JBorderLayout.h"

char* theJPanel = JPanel().Register();
JPanel* JPanel::create(JComponent* p, JComponent* item, int type) { 
  JPanel *panel = (JPanel*)createJComponent(theJPanel, p);
  if (panel) {
    JLayoutManager layout;
    JBorderLayout border;
    JCanvas *client = JCanvas::create(panel);
    client->setLayout(layout);
    client->add(*item);
    panel->type = type;
    panel->item = item;
    panel->client = client;
    panel->setLayout(border);
    panel->add(JBorderLayout::CENTER, *client);
    if (type & VSCROLL) {
      panel->vscroll = JScroller::create(panel, JScroller::VERTICAL);
      panel->vscroll->setBackground(JColor::lightGray);
      panel->add(JBorderLayout::EAST, *panel->vscroll);
    }
    if (type & HSCROLL) {
      panel->hscroll = JScroller::create(panel, JScroller::HORIZONTAL);
      panel->hscroll->setBackground(JColor::lightGray);
      panel->add(JBorderLayout::SOUTH, *panel->hscroll);
    }
  }
  return panel;
}

const char* JPanel::className() const { return "JPanel";}
JObject* JPanel::clone() const { return new JPanel(*this);}

JPanel::JPanel() {
  type = xOfs = yOfs = null;
  vscroll = hscroll = null; 
  item = client = null;
}

void JPanel::layout() {
  int oxOfs = xOfs;
  int oyOfs = yOfs;
  JDimension preferred;
  if (client) {
    JComponent::layout();
    preferred = getItemPreferredSize();
    if (vscroll) vscroll->show(height < preferred.height);
    if (hscroll) hscroll->show(width < preferred.width);
    JComponent::layout();
    item->reshape(-xOfs, -yOfs, client->width+xOfs, client->height+yOfs);
    preferred = item->preferredSize();
    if (vscroll) {
      vscroll->setValue(yOfs, client->height, 
        0, preferred.height, true);
      yOfs = vscroll->getValue();
    }
    if (hscroll) {
      hscroll->setValue(xOfs, client->width, 
        0, preferred.width, true);
      xOfs = hscroll->getValue();
    }
    if ((xOfs != oxOfs) || (yOfs != oyOfs)) {
      item->reshape(-xOfs, -yOfs, 
        client->width+xOfs, client->height+yOfs);
      preferred = item->preferredSize();
    }
    JComponent *parent = getParent();
    if (parent->getParent() == theRootWindow) {
      int dx = max(0, client->width-preferred.width);
      int dy = max(0, client->height-preferred.height);
      if ((dx > 0) || (dy > 0)) {
        peekMessage();
        JRect rect = *parent;
        parent->reshape(rect.x, rect.y, rect.width-dx, rect.height-dy);
      }
    }
  } else JComponent::layout();
}

JDimension JPanel::preferredSize() {
  if (item) {
    JDimension sz = getItemPreferredSize();
    if (vscroll && (height < sz.height))
      sz.width+=vscroll->width;
    if (hscroll && (width < sz.width))
      sz.height+=hscroll->height;
    return sz;
  }
  return JComponent::preferredSize();
}

JDimension JPanel::minimumSize() {
  if (item) {
    JDimension sz = getItemMinimumSize();
    if (vscroll && (height < sz.height))
      sz.width+=vscroll->width;
    if (hscroll && (width < sz.width))
      sz.height+=hscroll->height;
    return sz;
  }
  return JComponent::minimumSize();
}

boolean JPanel::action(JEvent& e, JObject* arg) {
  if (!e.target) return true;
  if (e.target == vscroll) {
    if (client) {
      JDimension sz = client->size();
      yOfs = e.key;
      item->reshape(-xOfs, -yOfs, sz.width+xOfs, sz.height+yOfs);
      item->updateInvalidArea();
    }
    return true;
  } else if (e.target == hscroll) {
    if (client) {
      JDimension sz = client->size();
      xOfs = e.key;
      item->reshape(-xOfs, -yOfs, sz.width+xOfs, sz.height+yOfs);
      item->updateInvalidArea();
    }
    return true;
  }
  return false;
}

JDimension JPanel::getItemPreferredSize() {
  int iw = item->width;
  item->width = width+xOfs;
  JDimension preferred = item->preferredSize();
  item->width = iw;
  return preferred;
}

JDimension JPanel::getItemMinimumSize() {
  int iw = item->width;
  item->width = width+xOfs;
  JDimension minimum = item->minimumSize();
  item->width = iw;
  return minimum;
}
