#include <stdio.h>
#include <stdlib.h>
#include "JSystem.h"
#include "JNullPointerException.h"
#define MAXDEBUG 65535
static int allocCount = 0;
static int debugCount = 0;
static int debugMax = 0;
static void* debug[MAXDEBUG];

void* operator new(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    static int nCounter = 0;
    if (!nCounter++)
      throw new JNullPointerException("Free Store Exhaust.");
  }
  allocCount++;
  if (debugCount++ == 0) {
    for (int i=0; i<MAXDEBUG; i++) 
      debug[i] = null;
  }
  if (debugCount > debugMax) debugMax = debugCount;
  int id = ((int)ptr)%MAXDEBUG;
  int base = id;
  while (debug[id]) {
    id=(id+1)%MAXDEBUG;
    if (id == base) {
      printf("Table Full for ptr %d.\n", ptr);
      return ptr;
    }
  }
  debug[id] = ptr;
  return ptr;
}

void operator delete(void* ptr) { 
  free(ptr);
  if (!ptr) {
    printf("delete null.\n");
    return;
  }
  int id = ((int)ptr)%MAXDEBUG;
  int base = id;
  while (debug[id]!=ptr) {
    id=(id+1)%MAXDEBUG;
    if (id == base) {
      printf("ptr %d not found.\n", ptr);
      return;
    }
  }
  debug[id] = 0;
  if (--debugCount == 0) {
#if defined(WIN32)
    JSystem::messageBeep();
#endif
    printf("Just Make. Max JObject=%d, Totle alloc=%d, %d\n",
      debugMax, allocCount, debugCount);
#if defined(BC5)
    scanf("%c", &debugCount);
#endif
  }
  /*printf("%d\n", debugCount);*/
}
