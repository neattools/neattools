#include "JMath.h"
#include "JRandom.h"
#include "JArithmeticException.h"
#include <errno.h>
#include <math.h>

double JMath::e = 2.7182818284590452354;
double JMath::pi = 3.14159265358979323846;

const char* JMath::className() const { return "JMath";}
JMath::JMath() {}

double JMath::sin(double x) { return ::sin(x);}
double JMath::cos(double x) { return ::cos(x);}
double JMath::tan(double x) { return ::tan(x);}
double JMath::asin(double x) { return ::asin(x);}
double JMath::acos(double x) { return ::acos(x);}
double JMath::atan(double x) { return ::atan(x);}
double JMath::exp(double x) { return ::exp(x);}

void checkError() {
  if (errno == EDOM) {
    errno = null;
    throw new JArithmeticException("Domain error.");
  } else if (errno == ERANGE) {
    errno = null;
    throw new JArithmeticException("Range error.");
  }
}

double JMath::log(double x) {
  double result = ::log(x);
  checkError();
  return result;
}

double JMath::sqrt(double x) {
  double result = ::sqrt(x);
  checkError();
  return result;
}

double JMath::mod(double a, double b) { return ::fmod(a, b);}
double JMath::ceil(double x) { return ::ceil(x);}
double JMath::floor(double x) { return ::floor(x);}
double JMath::rint(double x) { return (double)(int)x;}

double JMath::atan2(double y, double x) {
  if ((x==0.0)&&(y==0.0)) return 0.0;
  if (x==0.0) {
    if (y>=0) return pi/2.0;
    return -pi/2.0;
  } else if (y==0.0) {
    if (x>=0) return 0.0;
    return pi;
  }
  return ::atan2(y, x);
}

double JMath::pow(double a, double b) {
  double result = ::pow(a, b);
  checkError();
  return result;
}

int JMath::iabs(int x) { return ((x < 0) ? -x : x);}

int JMath::imod(int x, int y) {
  if (y <= 0) return 0;
  x = x%y;
  if (x < 0) x = (x+y)%y;
  return x;
}

int JMath::ipow(int a, int b) {
  int z = 1;
  int x = a;
  int y = b;
  while (y > 0) {
    if (y % 2 == 0) {
      x*=x; y/=2;
    } else {
      z*=x; y--;
    }
  }
  return z;
}

int JMath::round(double a) { return (int)::floor(a + 0.5);}
static JRandom JMathRandom;
int JMath::rand() { return JMathRandom.next();}
double JMath::random() { return JMathRandom.nextDouble();}

jcomplex JMath::conjg(const jcomplex& c) {
  return jcomplex(c.r, -c.i);
}

jcomplex JMath::polar(double r, double theta) {
  return jcomplex(r*::cos(theta), r*::sin(theta));
}

jcomplex JMath::sin(const jcomplex& c) {
  return (exp(jcomplex(-c.i, c.r))-exp(jcomplex(c.i, -c.r)))/jcomplex(0.0, 2.0);
}

jcomplex JMath::cos(const jcomplex& c) {
  return (exp(jcomplex(-c.i, c.r))+exp(jcomplex(c.i, -c.r)))/2.0;
}

jcomplex JMath::tan(const jcomplex& c) {
  return (exp(jcomplex(-c.i, c.r))-exp(jcomplex(c.i, -c.r)))/
    ((exp(jcomplex(-c.i, c.r))+exp(jcomplex(c.i, -c.r)))*jcomplex(0.0, 1.0));
}

jcomplex JMath::sinh(const jcomplex& c) {
  return (exp(c)-exp(-c))/2.0;
}

jcomplex JMath::cosh(const jcomplex& c) {
  return (exp(c)+exp(-c))/2.0;
}

jcomplex JMath::tanh(const jcomplex& c) {
  return (exp(c)-exp(-c))/(exp(c)+exp(-c));
}

jcomplex JMath::exp(const jcomplex& c) {
  return polar(::exp(c.r), c.i);
}

