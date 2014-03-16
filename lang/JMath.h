#if !defined( _JMath_h )
#define _JMath_h

#include "JObject.h"
#include "bcomplex.h"

#define jabs(x) (((x)>0)?(x):-(x))
#define jsign(x) (((x)>0)?(1):(-1))
#define sabs(x, y) (jsign(x)*jabs(y))
#define cmp(x, y) ((x==y)?0:((x>y)?1:-1))

class
#include "JBase.hpp"
JMath : public JObject {
  public:
    static double e;
    static double pi;
    static double sin(double x);
    static double cos(double x);
    static double tan(double x);
    static double asin(double x);
    static double acos(double x);
    static double atan(double x);
    static double exp(double x);
    static double log(double x);
    static double sqrt(double x);
    static double mod(double x, double y);
    static double ceil(double x);
    static double floor(double x);
    static double rint(double x);
    static double atan2(double y, double x);
    static double pow(double a, double b);
    static int ipow(int a, int b);
    static int imod(int x, int y);
    static int iabs(int x);
    static int round(double a);
    static int rand();
    static double random();
    static jcomplex conjg(const jcomplex& c);
    static jcomplex polar(double r, double theta = 0.0);
    static jcomplex sin(const jcomplex& c);
    static jcomplex cos(const jcomplex& c);
    static jcomplex tan(const jcomplex& c);
    static jcomplex sinh(const jcomplex& c);
    static jcomplex cosh(const jcomplex& c);
    static jcomplex tanh(const jcomplex& c);
    static jcomplex exp(const jcomplex& c);
    static jcomplex log(const jcomplex& c);
    static jcomplex sqrt(const jcomplex& c);
    static jcomplex pow(const jcomplex& c, double x);
    static jcomplex pow(double x, const jcomplex& c);
    static jcomplex pow(const jcomplex& c1, const jcomplex& c2);
    virtual const char* className() const;
  private:
    JMath();
};

#endif
