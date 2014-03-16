#include <stdio.h>
#include <sys/timeb.h>

long currentTimeMillis() {
  struct _timeb tstruct;
  _ftime(&tstruct);
  return tstruct.time*1000+tstruct.millitm;
}

class benchmark {
  public:
    int dummy(int i) { return i;}
    void start() {
      int i, x;
      x = 0;
      
      printf("Benchmark Start\n");
      long b1 = currentTimeMillis(), b2;
      for (i=0; i<100000000; i++) {
      }
      b2 = currentTimeMillis();
      printf("Empty For Loop %d\n", b2-b1);
      b1 = b2 = currentTimeMillis();
      for (i=0; i<100000000; i++) {
        x += i;
      }
      b2 = currentTimeMillis();
      printf("For Loop with + and assign %d\n", b2-b1);
      b1 = b2 = currentTimeMillis();
      for (i=0; i<100000000; i++) {
        x *= i;
      }
      b2 = currentTimeMillis();
      printf("For Loop with * and assign %d\n", b2-b1);
      b1 = b2 = currentTimeMillis();
      for (i=0; i<100000000; i++) {
        x += dummy(i);
      }
      b2 = currentTimeMillis();
      printf("For Loop with function call and assign %d\n", b2-b1);
    }
};

void main() {
  benchmark bm;
  bm.start();
}