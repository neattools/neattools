#if !defined( _JSeparator_h )
#define _JSeparator_h

#include "JCanvas.h"

class
#include "JAWT.hpp"
JSeparator : public JCanvas {
  public:
    enum { HORIZONTAL, VERTICAL};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JSeparator* create(JComponent* p, int _type);
    JSeparator();
    int getType();
    boolean setType(int _type);
    virtual boolean needRedraw();
  protected:
    int type;
};

#endif
