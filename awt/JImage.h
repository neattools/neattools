#if !defined( _JImage_h )
#define _JImage_h

#include "JReference.h"
#include "JGraphics.h"

class
#include "JAWT.hpp"
JImage : public JReference {
  protected:
    virtual void Delete();
    virtual int Duplicate();
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JImage();
    JImage(int handle, boolean ref = true);
    JImage(int _width, int _height);
    ~JImage();
    operator int();
    boolean isValid();
    int getWidth();
    int getHeight();
    JGraphics getJGraphics();
    JGraphics getJGraphics(class JComponent& c);
  protected:
    int width, height;
};

#endif
