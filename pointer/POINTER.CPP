
#include <stdio.h>

void main() {
   int x = 3;
   int &a = x;
   int *b = &x;
   printf("%d %d %d %d\n", a, &a, *&a, &x);
}