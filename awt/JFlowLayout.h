#if !defined( _JFlowLayout_h )
#define _JFlowLayout_h
#include "JComponent.h"

#include "JLayoutManager.h"
#include "JArray.h"

class
#include "JAWT.hpp"
JFlowLayout : public JLayoutManager {
  private:
    void moveComponents(JArray& item, int x, int y, int width, int height, int rowStart, int rowEnd);
  public:
    enum { CENTER, LEFT, RIGHT, JUSTIFY};
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual JDimension preferredLayoutSize(JComponent& parent);
    virtual JDimension minimumLayoutSize(JComponent& parent);
    virtual void layout(JComponent& parent);
    JFlowLayout();
    JFlowLayout(int _align);
    JFlowLayout(int _align, int _hgap, int _vgap);
  protected:
    int hgap, vgap, align;
};

#endif
