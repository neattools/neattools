#if !defined( _JJRandom_h )
#define _JJRandom_h

#include "JObject.h"

class
#include "JBase.hpp"
JRandom : public JObject {
  public:
    virtual const char* className() const;
    virtual int hashCode() const;
    virtual JObject* clone() const;
    virtual int compareTo(const JObject& s) const;
    JRandom();
    JRandom(long seed);
    void setSeed(long seed);
    int next();
    int nextInt(int mask);
    float nextFloat();
    double nextDouble();
  private:
    long seed;
    static long multiplier;
    static long addend;
};

#endif
