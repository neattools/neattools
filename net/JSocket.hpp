#if defined(WIN32) || defined(UNDER_CE)
  #include <windows.h>
  #include <winsock.h>
  #define socklen_t int
#else
  #if defined(solaris_sun4)
    #define socklen_t int
  #endif
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <netdb.h>
  #include <netinet/in.h>
  #define closesocket ::close
#endif

#if !defined(MAXHOSTNAMELEN)
  #define MAXHOSTNAMELEN 256
#endif

