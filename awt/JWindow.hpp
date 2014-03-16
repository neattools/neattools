#if !defined( _JWindowInclude_h )
#define _JWindowInclude_h

#include "JHashTable.h"

#if defined(WIN32)

  #include "filter.h"

  #define UM_DATA	(UM_FILTER+1)
  #define UM_AUX	(UM_FILTER+2)
  #define UM_DEBUG	(UM_FILTER+3)
  #define UM_IDLE	(UM_FILTER+4)

  class
#if defined(_AWT_LIB) 
#elif defined(_AWT_DLL)
  DllExport
#else
  DllImport 
#endif
  JMicroSoft {
    public:
      static HINSTANCE hInstance;
      static HINSTANCE hPrevInstance;
      static LPSTR lpszCmdLine;
      static int nCmdShow;
      static int theContextCount;
      static JHashTable JObjectCache;
      static boolean isWin32();
      static boolean isWin95();
      static boolean isWinNT();
      JMicroSoft(HINSTANCE _hInstance, 
        HINSTANCE _hPrevInstance,
        LPSTR _lpszCmdLine,
        int _nCmdShow);
      int MessageLoop();
      virtual void DefaultLoop();
  };

#else

  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
  #include <X11/Xresource.h>

  class
#if defined(_AWT_LIB) 
#elif defined(_AWT_DLL)
  DllExport
#else
  DllImport 
#endif
  JUNIX {
    public:
      JUNIX(int argc, char** argv);
      int MessageLoop();
      virtual void DefaultLoop();
      static void DispatchEvent(XEvent *event);
      static int theCounter;
      static Display *theDisplay;
      static Visual  *theVisual;
      static Colormap theColormap;
      static int theScreen;
      static int theVisualDepth;
      static int theEventMask;
      static int theDisableMask;
      static JHashTable JObjectCache;
      static int argc;
      static char** argv;
    protected:
      static XWMHints* p_XWMH;
      static XSizeHints* p_XSH;
      static XClassHint* p_CH;
  };

#endif

#endif
