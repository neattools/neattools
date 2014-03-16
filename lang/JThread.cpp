#include "JThread.h"

#include "JSystem.h"

#include "JThreadCreateException.h"



char* theJThread = JThread().Register();



DllExport void segmentDelay(int interval, int&base, int& counter, boolean& cond) {

  int delta;

  int tadjust = 0;

  int adjust = JSystem::currentTimeMillis()-base;

  counter = interval-adjust;

  if (counter < 0) {

    base-=counter;

    counter = 0;

    JThread::sleep(1);

  }

  while (cond && (counter > 0)) {

    delta = min(50, counter);

    tadjust += adjust+delta;

    JThread::sleep(delta);

    adjust = JSystem::currentTimeMillis()-

      base-tadjust;

    counter -= delta+adjust;

  }

  base+=interval;

}



#if defined(WIN32) || defined(UNDER_CE)

  #include <windows.h>



  DWORD FAR PASCAL CommJThreadProc(LPSTR lpData) {

    ((JObject*)lpData)->run();

    return null;

  }



#else



  #include <unistd.h>

  #include <signal.h>

  #include <sys/time.h>

  #include <pthread.h>



  typedef int HANDLE;

  

  void Sleep(unsigned int ms) { usleep(ms*1000);}



  void* CommJThreadProc(void *arg) {

    ((JObject*)arg)->run();

    return null;

  }



  void CloseHandle(HANDLE id) {

    if ((pthread_t)id == pthread_self()) {

      pthread_exit(null);

      return;

    }

  }



  HANDLE GetCurrentThread() { return (HANDLE)pthread_self();}



  int GetThreadPriority(HANDLE id) {

/*

    int policy;

    struct sched_param param;

    pthread_getschedparam((pthread_t)id, &policy, &param);

    return param.sched_priority;

*/

    return 0;

  }



  int SetThreadPriority(HANDLE id, int priority) {

/*

    struct sched_param param;

    param.sched_priority = priority;

    pthread_setschedparam((pthread_t)id, SCHED_RR, &param);

    return param.sched_priority;

*/

    return 0;

  }



  void SuspendThread(HANDLE id) {}

  void ResumeThread(HANDLE id) {}



#endif



int JThread::TMIN_PRIORITY = 1;

int JThread::TMAX_PRIORITY = 10;

int JThread::TNORM_PRIORITY = 5;



int JThread::toPlatform(int Priority) {

#if defined (WIN32)

  if (Priority > TNORM_PRIORITY+2) {

    return THREAD_PRIORITY_TIME_CRITICAL;

  } else if (Priority == TNORM_PRIORITY+2) {

    return THREAD_PRIORITY_HIGHEST;

  } else if (Priority == TNORM_PRIORITY+1) {

    return THREAD_PRIORITY_ABOVE_NORMAL;

  } else if (Priority == TNORM_PRIORITY-1) {

    return THREAD_PRIORITY_BELOW_NORMAL;

  } else if (Priority == TNORM_PRIORITY-2) {

    return THREAD_PRIORITY_LOWEST;

  } else if (Priority < TNORM_PRIORITY-2) {

    return THREAD_PRIORITY_IDLE;

  } else return THREAD_PRIORITY_NORMAL;

#else

  return (TNORM_PRIORITY-Priority);

#endif

}



int JThread::fromPlatform(int Priority) {

#if defined(WIN32)

  switch (Priority) {

    case THREAD_PRIORITY_TIME_CRITICAL:

      return TMAX_PRIORITY;

    case THREAD_PRIORITY_HIGHEST:

      return TNORM_PRIORITY+2;

    case THREAD_PRIORITY_ABOVE_NORMAL:

      return TNORM_PRIORITY+1;

    case THREAD_PRIORITY_BELOW_NORMAL:

      return TNORM_PRIORITY-1;

    case THREAD_PRIORITY_LOWEST:

      return TNORM_PRIORITY-2;

    case THREAD_PRIORITY_IDLE:

      return TMIN_PRIORITY;

    default:

      return TNORM_PRIORITY;

  }

#else

  return (TNORM_PRIORITY-Priority);

#endif

}



void JThread::Delete() {

  SuspendThread((HANDLE)hnd);

  CloseHandle((HANDLE)hnd);

}



int JThread::Duplicate() {

  start();

  return hnd;

}



const char* JThread::className() const { return "JThread";}

JObject* JThread::clone() const { return new JThread(*this);}



#if defined(WIN32)

int JThread::compareTo(const JObject& s) const {

  if (className() != s.className()) 

    return JObject::compareTo(s);

  return id-((JThread*)&s)->id;

}

#endif



JThread::JThread() {

  priority = TNORM_PRIORITY;

  ptarget = null;

#if defined(WIN32)

  id = 0;

#endif

}



JThread::JThread(JObject* target) {

  priority = TNORM_PRIORITY;

  ptarget = target;

#if defined(WIN32)

  id = 0;

#endif

}



#if defined(WIN32)

JThread::JThread(int handle, ulong _id) 

  : JReference(handle) {

  priority = fromPlatform(

    GetThreadPriority((HANDLE)handle));

  id = _id;

  ptarget = null;

}

#else

JThread::JThread(int handle) 

  : JReference(handle) {

  priority = fromPlatform(

    GetThreadPriority((HANDLE)handle));

  ptarget = null;

}

#endif



JThread::~JThread() { Release();}

JThread::operator int() { return hnd;}



void JThread::start() {

#if defined (WIN32)

  HANDLE td = CreateThread(

    (LPSECURITY_ATTRIBUTES)null,

    null, 

    (LPTHREAD_START_ROUTINE)CommJThreadProc,

    (LPVOID)(ptarget ? ptarget : this),

    null, 

    &id);

  if (!td)

    throw new JThreadCreateException("CreateJThread");

  Allocate((int)td);

#else

  pthread_t id;

  if (pthread_create(&id, NULL, CommJThreadProc, 

    (ptarget) ? ptarget : this))

    throw new JThreadCreateException("CreatePThread");

  Allocate((int)id);

#endif

}



void JThread::run() {}



boolean JThread::isAlive() {

  return (hnd != null);

}



void JThread::stop() { Release();}



void JThread::suspend() {

  SuspendThread((HANDLE)hnd);

}



void JThread::resume() {

  ResumeThread((HANDLE)hnd);

}



void JThread::setPriority(int newPriority) { 

  if (newPriority > TMAX_PRIORITY) newPriority = TMAX_PRIORITY;

  if (newPriority < TMIN_PRIORITY) newPriority = TMIN_PRIORITY;

  priority = newPriority;

  SetThreadPriority((HANDLE)hnd,

    toPlatform(priority));

}



int JThread::getPriority() { return priority;}



long JThread::waitFor() {

  if (hnd == null) return null;

#if defined(WIN32)

  /*

  int WaitResult = null;

  const HANDLE* ha = (const HANDLE*)&hnd;

  do 

  {

    WaitResult = MsgWaitForMultipleObjects(1,     

    // only 1 wait object

      ha, // worker thread

      FALSE,   // stop if any

      INFINITE,  // no timeout

      QS_ALLINPUT);

    if (WaitResult == WAIT_OBJECT_0+1) 

    {

      // Handle windows message

      MSG Msg;

      if (PeekMessage(&Msg,NULL,0,0,PM_REMOVE)) 

      {

        DispatchMessage(&Msg);

      }

    }

  } while (WaitResult == WAIT_OBJECT_0+1);

  return WaitResult;

  */

  return WaitForSingleObject((HANDLE)hnd, INFINITE);

#else

  return pthread_join((pthread_t)hnd, null);

#endif

}



JThread JThread::currentJThread() { 

#if defined(WIN32)

  return JThread((int)GetCurrentThread(),

    (ulong)GetCurrentThreadId());

#else

  return JThread((int)GetCurrentThread());

#endif

} 



void JThread::yield() { 

  JThread::sleep(100);

}



void JThread::sleep(ulong ms) { 

  Sleep(ms);

}

