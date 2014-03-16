#if !defined( _JWindow_h )
#define _JWindow_h

#include "JComponent.h"

class
#include "JAWT.hpp"
JWindow : public JComponent {
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JWindow* create();
};

#endif
