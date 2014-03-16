#if !defined( _JTriangleButton_h )
#define _JTriangleButton_h

#include "JPushButton.h"

class
#include "JAWT.hpp"
JTriangleButton : public JPushButton {
  public:
    enum { LEFT, RIGHT, UP, DOWN};
    virtual const char* className() const;
    virtual JObject* clone() const;
    static JTriangleButton* create(JComponent *p);
    JTriangleButton();
    int getType();
    boolean setType(int _type);
    virtual void paint(JGraphics g);
  protected:
    int type;
};

#endif
