#include "JCriticalSection.h"

char* theJCriticalSection = JCriticalSection().Register();
const char* JCriticalSection::className() const { return "JCriticalSection";}
JObject* JCriticalSection::clone() const { return new JCriticalSection(*this);}
JCriticalSection::~JCriticalSection() { Release();}

#if defined(WIN32) || defined(UNDER_CE)

  #include <windows.h>

  JCriticalSection::JCriticalSection() { Allocate(Duplicate());}

  void JCriticalSection::Delete() {
    DeleteCriticalSection((CRITICAL_SECTION*)hnd);
    delete (CRITICAL_SECTION*)hnd;
  }

  int JCriticalSection::Duplicate() {
    CRITICAL_SECTION *cs = new CRITICAL_SECTION;
    InitializeCriticalSection(cs);
    return (int)cs;
  }

  void JCriticalSection::lock() 
  { EnterCriticalSection((CRITICAL_SECTION*)hnd);}

  void JCriticalSection::unlock() 
  { LeaveCriticalSection((CRITICAL_SECTION*)hnd);}

#else

  #include <pthread.h>

  JCriticalSection::JCriticalSection() {
    count = null;
    thread = null;
    Allocate(Duplicate());
  }

  void JCriticalSection::Delete() {
    pthread_mutex_destroy((pthread_mutex_t*)hnd);
    delete (pthread_mutex_t*)hnd;
  }

  int JCriticalSection::Duplicate() {
    pthread_mutex_t *mutex = new pthread_mutex_t;
    pthread_mutex_init(mutex, NULL);
    return (int)mutex;
  }

  void JCriticalSection::lock() {
    if (!count) {
      count++;
      thread = (int)pthread_self();
    } else if (thread == (int)pthread_self()) {
      count++;
      return;
    }
    if (!hnd) {
      Allocate(Duplicate());
    }
    pthread_mutex_lock((pthread_mutex_t*)hnd);
  }

  void JCriticalSection::unlock() { 
    if (thread == (int)pthread_self()) {
      if (--count) return;
      thread = null;
    }
    pthread_mutex_unlock((pthread_mutex_t*)hnd);
  }

#endif
