#if !defined( _JGridLayout_h )
#define _JGridLayout_h

#include "JLayoutManager.h"
#include "JComponent.h"

class
#include "JAWT.hpp"
JGridLayout : public JLayoutManager {
  public:
    enum { CENTER, LEFT, RIGHT};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual JDimension preferredLayoutSize(JComponent& parent);
    virtual JDimension minimumLayoutSize(JComponent& parent);
    virtual void layout(JComponent& parent);
    JGridLayout();
    JGridLayout(int _rows, int _cols);
    JGridLayout(int _rows, int _cols, int _hgap, int _vgap);
  protected:
    int hgap, vgap, rows, cols;
};

#endif
