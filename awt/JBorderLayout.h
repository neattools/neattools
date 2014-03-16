#if !defined( _JBorderLayout_h )
#define _JBorderLayout_h

#include "JLayoutManager.h"
#include "JComponent.h"

class
#include "JAWT.hpp"
JBorderLayout : public JLayoutManager {
  public:
    enum { NORTH, SOUTH, EAST, WEST, CENTER, LAST};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void addLayoutComponent(int type, JComponent& comp);
    virtual void removeLayoutComponent(JComponent& comp);
    virtual JDimension preferredLayoutSize(JComponent& parent);
    virtual JDimension minimumLayoutSize(JComponent& parent);
    virtual void layout(JComponent& parent);
    JBorderLayout();
    JBorderLayout(int _hgap, int _vgap);
  protected:
    int hgap, vgap;
    JComponent *item[5];
};

#endif
