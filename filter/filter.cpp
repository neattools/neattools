#include "Filter.h"

//#define _DEBUG
#define MAX_CLASS_NAME 256

BOOL isNeatTools(HWND hwnd) {
  char buf[MAX_CLASS_NAME];
  GetClassName(hwnd, buf, MAX_CLASS_NAME);
  return (strcmp(buf, CLASSNAME) == 0);
}

BOOL CALLBACK EnumWindowsSendProc(HWND hwnd, LPARAM lparm) {
  if (isNeatTools(hwnd)) {
    SendMessage(hwnd, WM_COPYDATA, 
      (WPARAM)NULL, lparm);
  }
  return TRUE;
}

LRESULT APIENTRY KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode > -1) {
    FILTERDATA gfmd;
    gfmd.wParam = wParam;
    gfmd.lParam = lParam;
    COPYDATASTRUCT gcds = { UM_KEYBOARD, sizeof(FILTERDATA), &gfmd };
    EnumWindows(EnumWindowsSendProc, (LPARAM)&gcds);
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT APIENTRY MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode > -1) {
    LPMOUSEHOOKSTRUCT lpMHS = (LPMOUSEHOOKSTRUCT)lParam;
    if ((lpMHS->hwnd) && (wParam != WM_NCHITTEST)) {
      FILTERDATA gfmd;
      gfmd.wParam = wParam;
      *(LPMOUSEHOOKSTRUCT)gfmd.extraData = *lpMHS;
      BOOL isNeat = isNeatTools(lpMHS->hwnd);
      COPYDATASTRUCT gcds = { UM_MOUSE, sizeof(FILTERDATA), &gfmd };
      EnumWindows(EnumWindowsSendProc, (LPARAM)&gcds);
    }
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT APIENTRY GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if ((nCode > -1) && (wParam == PM_REMOVE)) {
    LPMSG lpMSG = (LPMSG)lParam;
    if ((lpMSG->hwnd) && (lpMSG->message == WM_MOUSEWHEEL)) {
      FILTERDATA gfmd;
      gfmd.wParam = lpMSG->message;
      *(LPMSG)gfmd.extraData = *lpMSG;
      COPYDATASTRUCT gcds = { UM_GETMESSAGE, sizeof(FILTERDATA), &gfmd };
      EnumWindows(EnumWindowsSendProc, (LPARAM)&gcds);
    }
  }
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

static HINSTANCE hInstance = 0;
static int counter = 0;
static HHOOK hMouse = 0;
static HHOOK hKeyboard = 0;
static HHOOK hGetMessage = 0;

DllExport void APIENTRY initialize_filter() {
  if (!counter++) {
#if !defined(_DEBUG)
    hMouse = SetWindowsHookEx(   
      WH_MOUSE, (HOOKPROC)MouseProc,
      hInstance, (DWORD)0L);
    hKeyboard = SetWindowsHookEx(
      WH_KEYBOARD, (HOOKPROC)KeyboardProc,
      hInstance, (DWORD)0L);
    hGetMessage = SetWindowsHookEx(
      WH_GETMESSAGE, (HOOKPROC)GetMessageProc,
      hInstance, (DWORD)0L);
#endif
  }
}

DllExport void APIENTRY destroy_filter() {
  if (!--counter) {
#if !defined(_DEBUG)
    UnhookWindowsHookEx(hMouse);
    UnhookWindowsHookEx(hKeyboard);
    UnhookWindowsHookEx(hGetMessage);
#endif
  }
}

BOOL APIENTRY DllMain(HINSTANCE _hInstance,
  DWORD ulReason, LPVOID lpReserved) {
  hInstance = _hInstance;
  return TRUE;
}
