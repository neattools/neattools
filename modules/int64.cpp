#include "int64.h"

int64::int64() { lo = hi = 0;}

int64::int64(int x) {
  if (x < 0) {
    hi = -1;
    lo = x;
  } else {
    hi = 0;
    lo = x;
  }
}

int64::int64(uint _lo, int _hi) { lo = _lo; hi = _hi;}

int int64::operator==(int64 x) { return (hi == x.hi) && (lo == x.lo);}
int int64::operator!=(int64 x) { return (hi != x.hi) || (lo != x.lo);}
int int64::operator>=(int64 x) { return (hi > x.hi) || (hi == x.hi) && (lo >= x.lo);}
int int64::operator<=(int64 x) { return (hi < x.hi) || (hi == x.hi) && (lo <= x.lo);}
int int64::operator> (int64 x) { return (hi > x.hi) || (hi == x.hi) && (lo >  x.lo);}
int int64::operator< (int64 x) { return (hi < x.hi) || (hi == x.hi) && (lo <  x.lo);}

int64 int64::operator+(int64 x) {
  int64 result;
  if (0xffffffff-lo < x.lo) {
    result.hi = hi+x.hi+1;
  } else {
    result.hi = hi+x.hi;
  }
  result.lo = lo+x.lo;
  return result;
}

int64& int64::operator+=(int64 x) {
  int64 result;
  if (0xffffffff-lo < x.lo) {
    hi += x.hi+1;
  } else {
    hi += x.hi;
  }
  lo += x.lo;
  return *this;
}

int64 int64::operator-(int64 x) {
  int64 result;
  if (lo < x.lo) {
    result.hi = hi-x.hi-1;
  } else {
    result.hi = hi-x.hi;
  }
  result.lo = lo-x.lo;
  return result;
}

int64& int64::operator-=(int64 x) {
  int64 result;
  if (lo < x.lo) {
    hi -= x.hi+1;
  } else {
    hi -= x.hi;
  }
  lo -= x.lo;
  return *this;
}

int64 int64::operator-() {
  int64 result(~lo, ~hi);
  return result+=1;
}

