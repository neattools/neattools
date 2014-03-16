#if !defined(_Filter_h)
#define _Filter_h

#include <windows.h>

#if defined(BC5)
  #pragma option -w-par
#endif

#if defined(WIN32)
  #define DllImport __declspec(dllimport)
  #define DllExport __declspec(dllexport)
#else
  #define DllImport
  #define DllExport
#endif

#define CLASSNAME	"JMainWindow"
#define DLLNAME		"filter"
#define HK_SOURCE	0
#define HK_COUNT	4
#define UM_MOUSE	(WM_USER)
#define UM_KEYBOARD	(WM_USER+1)
#define UM_GETMESSAGE   (WM_USER+2)
#define UM_FILTER       (WM_USER+3)

//
// Must use SendMessage to avoid deadlock on popup menu
//

typedef struct {
  WPARAM wParam;
  union {
    LPARAM lParam;
    BYTE extraData[64];
  };
} FILTERDATA, *PFILTERDATA;

#endif