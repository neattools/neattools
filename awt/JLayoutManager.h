#if !defined( _JLayoutManager_h )
#define _JLayoutManager_h

#include "JString.h"
#include "JDimension.h"

class
#include "JAWT.hpp"
JLayoutManager : public JObject {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    virtual void addLayoutComponent(int type, class JComponent& comp);
    virtual void removeLayoutComponent(class JComponent& comp);
    virtual JDimension preferredLayoutSize(class JComponent& parent);
    virtual JDimension minimumLayoutSize(class JComponent& parent);
    virtual void layout(class JComponent& parent);
};

#endif
