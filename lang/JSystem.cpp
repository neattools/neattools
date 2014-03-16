#include "JSystem.h"
#include "JDate.h"

#if defined (WIN32)
  #include <windows.h>
#else
  #include <stdio.h>
#endif

const char* JSystem::className() const { return "JSystem";}

int JSystem::currentTimeMillis() {
#if defined(WIN32_TIME)
  JDate date;
  return date.getITime()*1000+date.getMillis();
#else
  struct _timeb_ tstruct;
  _ftime_(&tstruct);
  return tstruct.time*1000+tstruct.millitm;
#endif
}

void JSystem::messageBeep() {
#if defined(WIN32)
  MessageBeep(0xFFFF);
#else
  printf("\007");
#endif
}

JSystem::JSystem() {}
