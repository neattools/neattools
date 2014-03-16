#if !defined( _JRegion_h )
#define _JRegion_h

#include "JReference.h"
#include "JRect.h"

class
#include "JAWT.hpp"
JRegion : public JReference {
  protected:
    virtual void Delete();
    virtual int Duplicate();
  public:
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRegion();
    JRegion(JRect rect);
    JRegion(int x, int y, int width, int height);
    JRegion(int* xs, int *ys, int nPoints);
    ~JRegion();
    operator int();
    operator JRect();
    boolean operator!();
    boolean operator||(const JRegion& reg);
    boolean operator&&(const JRegion& reg);
    JRegion operator|(const JRegion& reg);
    JRegion operator&(const JRegion& reg);
    JRegion operator-(const JRegion& reg);
    JRegion operator^(const JRegion& reg);
    JRegion& operator|=(const JRegion& reg);
    JRegion& operator&=(const JRegion& reg);
    JRegion& operator-=(const JRegion& reg);
    JRegion& operator^=(const JRegion& reg);
  protected:
    JRect rect;
    JRect calculate();
};

#endif
