#if !defined( _int64_h )
#define _int64_h

#include "JObject.h"

class int64 {
  public:
    int64();
    int64(int x);
    int64(uint _lo, int _hi);
    int operator==(int64 x);
    int operator!=(int64 x);
    int operator>=(int64 x);
    int operator<=(int64 x);
    int operator> (int64 x);
    int operator< (int64 x);
    int64 operator+(int64 x);
    int64& operator+=(int64 x);
    int64 operator-(int64 x);
    int64& operator-=(int64 x);
    int64 operator-();
    uint lo;
    int hi;
};

#endif
