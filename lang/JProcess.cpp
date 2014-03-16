#include "JProcess.h"
#include "JProcessCreateException.h"
#include <stdlib.h>

char* theJProcess = JProcess().Register();

#if defined(WIN32)
  #include <windows.h>
#else
  #include <unistd.h>
  #include <sys/wait.h>
  #include <malloc.h>
  #include <string.h>

  typedef int HANDLE;
  extern int CloseHandle(HANDLE id);
  HANDLE GetCurrentProcess() { return (HANDLE)getpid();}
#endif

void JProcess::Delete() {
  CloseHandle((HANDLE)hnd);
}

int JProcess::Duplicate() {
  start();
  return hnd;
}

const char* JProcess::className() const { return "JProcess";}
int JProcess::hashCode() const { return hashMask & hnd;}
JObject* JProcess::clone() const { return new JProcess(*this);}
JProcess::JProcess() {}

JProcess::JProcess(const JString& _cmdLine) {
  cmdLine = _cmdLine;
}

JProcess::JProcess(char **argv) {
  int i=0;
  cmdLine = argv[i++];
  while (argv[i]) 
    cmdLine += JString(" ")+JString(argv[i++]);
}

JProcess::JProcess(int hJProcess) 
  : JReference(hJProcess) {
  mainJThread = JThread::currentJThread();
}

JProcess::~JProcess() { Release();}

void JProcess::start() {
#if defined (WIN32) || defined(UNDER_CE)
  PROCESS_INFORMATION pi;
  if (!CreateProcess(
    null,
    (char*)cmdLine,
    (LPSECURITY_ATTRIBUTES)null,
    (LPSECURITY_ATTRIBUTES)null,
    false, null, null, null, null, &pi))
    throw new JProcessCreateException("CreateJProcess");
  Allocate((int)pi.hProcess);
  mainJThread.Allocate((int)pi.hThread);
#else
  int id;
  if (!(id = fork())) {
    int argc = 0, i;
    char *ptr = cmdLine, **argv;
    Allocate((int)getpid());
    do {
      ptr = strchr(ptr, ' ');
      argc++;
    } while (ptr++);
    argv = new char*[argc+1];
    argv[i=0] = ptr = cmdLine;
    do {
      ptr = strchr(ptr, ' ');
      if (ptr) {
        *ptr++ = 0;
        argv[++i] = ptr;
      }
    } while (ptr);
    argv[argc] = null;
    execvp(argv[0], argv);
    exit(1);
  } else {
    if (id < 0) 
      throw new JProcessCreateException("fork");
    Allocate(id);
    mainJThread = JThread(id);
  }
#endif
}

boolean JProcess::isAlive() {
  return (hnd != null);
}

void JProcess::stop() { Release();}

void JProcess::suspend() {
  mainJThread.suspend();
}

void JProcess::resume() {
  mainJThread.resume();
}

void JProcess::setPriority(int newPriority) { 
  mainJThread.setPriority(newPriority);
}

int JProcess::getPriority() 
{ return mainJThread.getPriority();}

long JProcess::waitFor() {
#if defined(WIN32) 
  return WaitForSingleObject((HANDLE)hnd, INFINITE);
#else
  int status;
  return waitpid((HANDLE)hnd, &status, null);
#endif
}

long JProcess::exitValue() {
#if defined(WIN32)
  DWORD exitCode;
  if (GetExitCodeProcess((HANDLE)hnd, &exitCode))
    return exitCode;
  throw new JRuntimeException("JProcess::exitValue");
  #if !defined(BC5)
  return null;
  #endif
#else
  int status;
  if (waitpid(hnd, &status, null) == hnd)
    return WEXITSTATUS(status);
  throw new JRuntimeException("JProcess::exitValue");
#endif
}

JProcess JProcess::currentJProcess() { 
  return JProcess((int)GetCurrentProcess());
}

void JProcess::exit(int status) { ::exit(status);}

long JProcess::freeMemory() {
#if defined(WIN32)
  MEMORYSTATUS ms;
  GlobalMemoryStatus(&ms);
  return ms.dwAvailPhys;
#else
//  struct mstats ms; // = mstats();
//  return (long)ms.bytes_free;
  return 0;
#endif
}

long JProcess::totalMemory() {
#if defined(WIN32)
  MEMORYSTATUS ms;
  GlobalMemoryStatus(&ms);
  return ms.dwTotalPhys;
#else
//  struct mstats ms; // = mstats();
//  return (long)ms.bytes_total;
  return 0;
#endif
}
