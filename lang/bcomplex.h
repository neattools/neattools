#if !defined( _jcomplex_h )
#define _jcomplex_h

#include "JObject.h"

class
#include "JBase.hpp"
jcomplex {
  public:
    double r, i;
    double norm() const { return r*r+i*i;}
    double abs() const;
    double arg() const;
    jcomplex(double _r = 0, double _i = 0) : r(_r), i(_i) {}
    jcomplex(const jcomplex& c) : r(c.r), i(c.i) {}
    jcomplex& operator=(const jcomplex& c) { r=c.r; i=c.i; return *this;}
    jcomplex& operator+=(const jcomplex& c) { r+=c.r; i+=c.i; return *this;}
    jcomplex& operator-=(const jcomplex& c) { r-=c.r; i-=c.i; return *this;}
    jcomplex& operator*=(const jcomplex& c);
    jcomplex& operator/=(const jcomplex& c);
    jcomplex& operator=(double _r) { r=_r; i=0; return *this;}
    jcomplex& operator+=(double _r) { r+=_r; return *this;}
    jcomplex& operator-=(double _r) { r-=_r; return *this;}
    jcomplex& operator*=(double _r) { r*=_r; i*=_r; return *this;} 
    jcomplex& operator/=(double _r) { r/=_r; i/=_r; return *this;}
    jcomplex operator+(const jcomplex& c) const { return jcomplex(r+c.r, i+c.i);}
    jcomplex operator-(const jcomplex& c) const { return jcomplex(r-c.r, i-c.i);}
    jcomplex operator*(const jcomplex& c) const;
    jcomplex operator/(const jcomplex& c) const;
    boolean operator==(const jcomplex& c) const { return (r == c.r) && (i == c.i);}
    boolean operator!=(const jcomplex& c) const { return (r != c.r) || (i != c.i);}
    friend jcomplex operator-(const jcomplex& c) { return jcomplex(-c.r, -c.i);}
    friend jcomplex operator+(const jcomplex& c, double _r) { return jcomplex(c.r+_r, c.i);}
    friend jcomplex operator+(double _r, const jcomplex& c) { return jcomplex(c.r+_r, c.i);}
    friend jcomplex operator-(const jcomplex& c, double _r) { return jcomplex(c.r-_r, c.i);}
    friend jcomplex operator-(double _r, const jcomplex& c) { return jcomplex(c.r-_r, c.i);}
    friend jcomplex operator*(const jcomplex& c, double _r) { return jcomplex(c.r*_r, c.i*_r);}
    friend jcomplex operator*(double _r, const jcomplex& c) { return jcomplex(c.r*_r, c.i*_r);}
    friend jcomplex operator/(const jcomplex& c, double _r) { return jcomplex(c.r/_r, c.i/_r);}
    friend jcomplex operator/(double _r, const jcomplex& c) { return jcomplex(c.r, c.i);}
    friend boolean operator==(const jcomplex& c, double _r) { return (c.r == _r) && (c.i == 0.0);}
    friend boolean operator==(double _r, const jcomplex& c) { return (c.r == _r) && (c.i == 0.0);}
    friend boolean operator!=(const jcomplex& c, double _r) { return (c.r != _r) || (c.i != 0.0);}
    friend boolean operator!=(double _r, const jcomplex& c) { return (c.r != _r) || (c.i != 0.0);}
};

#endif
