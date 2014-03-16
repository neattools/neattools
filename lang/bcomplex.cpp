#include "bcomplex.h"
#include "JMath.h"

double jcomplex::abs() const { // ???? Please correct me
  return JMath::sqrt(r*r+i*i);
}

double jcomplex::arg() const {
  return JMath::atan2(i, r);
}

jcomplex& jcomplex::operator*=(const jcomplex& c) {
  double _r = r*c.r - i*c.i;
  i = r*c.i + i*c.r;
  r = _r;
  return *this;
}

jcomplex& jcomplex::operator/=(const jcomplex& c) {
  double d = c.norm();
  double _r = (r*c.r + i*c.i)/d;
  i = (i*c.r - r*c.i)/d;
  r= _r;
  return *this;
}

jcomplex jcomplex::operator*(const jcomplex& c) const {
  return jcomplex(r*c.r - i*c.i, r*c.i + i*c.r);
}

jcomplex jcomplex::operator/(const jcomplex& c) const {
  double d = c.norm();
  return jcomplex((r*c.r + i*c.i)/d, (i*c.r - r*c.i)/d);
}

