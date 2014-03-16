#if defined(WIN32) || defined(UNDER_CE)
  #define WIN32_TIME
#endif

#if defined(WIN32_TIME)
  #include <windows.h>
#else 
  #include <time.h>
  #include <sys/timeb.h>
  #if defined (WIN32)
    #define _tzset_ _tzset
    #define _timeb_ _timeb
    #define _ftime_ _ftime
  #else
    #define _tzset_ tzset
    #define _timeb_ timeb
    #define _ftime_ ftime

    typedef struct _SYSTEMTIME {
      short wYear;
      short wMonth;
      short wDayOfWeek;
      short wDay;
      short wHour;
      short wMinute;
      short wSecond;
      short wMilliseconds;
    } SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

  #endif
#endif

