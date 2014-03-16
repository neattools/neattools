// tester.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tester.h"
#include "mmsystem.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HWND hwndList;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void GetComponentType(MIXERLINE* mxl, LPWSTR name) {
  switch (mxl->dwComponentType) {
    case MIXERLINE_COMPONENTTYPE_DST_DIGITAL:
      lstrcpy(name, TEXT("DST_DIGITAL"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES:
      lstrcpy(name, TEXT("DST_HEADPHONES"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_LINE:
      lstrcpy(name, TEXT("DST_LINE"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_MONITOR:
      lstrcpy(name, TEXT("DST_MONITOR"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS:
      lstrcpy(name, TEXT("DST_SPEAKERS"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE:
      lstrcpy(name, TEXT("DST_TELEPHONE"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED:
      lstrcpy(name, TEXT("DST_UNDEFINED"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_VOICEIN:
      lstrcpy(name, TEXT("DST_VOICEIN"));
      break;
    case MIXERLINE_COMPONENTTYPE_DST_WAVEIN:
      lstrcpy(name, TEXT("DST_WAVEIN"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_ANALOG:
      lstrcpy(name, TEXT("SRC_ANALOG"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY:
      lstrcpy(name, TEXT("SRC_AUXILIARY"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC:
      lstrcpy(name, TEXT("SRC_COMPACTDISC"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:
      lstrcpy(name, TEXT("SRC_DIGITAL"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_LINE:
      lstrcpy(name, TEXT("SRC_LINE"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE:
      lstrcpy(name, TEXT("SRC_MICROPHONE"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER:
      lstrcpy(name, TEXT("SRC_PCSPEAKER"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER:
      lstrcpy(name, TEXT("SRC_SYNTHESIZER"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE:
      lstrcpy(name, TEXT("SRC_TELEPHONE"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED:
      lstrcpy(name, TEXT("SRC_UNDEFINED"));
      break;
    case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT:
      lstrcpy(name, TEXT("SRC_WAVEOUT"));
      break;
    default:
      lstrcpy(name, TEXT("UNDEFINED"));
  }
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE: 
	  {
	    RECT rc;
	    GetWindowRect(hWnd, &rc);
            hwndList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE,
              0, 0, rc.right-rc.left, rc.bottom-rc.top,
              hWnd, (HMENU)1, hInst, NULL);
	    break;
	  }
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
		  {
		    //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		    SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
		    int numDevs = mixerGetNumDevs();
		    if (numDevs == 0) {
		      MessageBox(hWnd, TEXT("No audio mixer devices found."), NULL, MB_OK);
		      break;
		    }
#define MSG_LEN 1024
		    TCHAR msg[MSG_LEN+1];
		    TCHAR lpszComponent[MSG_LEN];
		    UINT nDevId = 0, uDest, uConnect, uConnections;
		    MIXERCAPS mxcaps;
		    MMRESULT rc;
		    HMIXER hmx = NULL;
		    for (int i=0; i<numDevs; i++) {
		      mixerGetDevCaps(i, &mxcaps, sizeof(MIXERCAPS));
		      wsprintf(msg, TEXT("Device name: %s\t#Destinations: %ld"), mxcaps.szPname, mxcaps.cDestinations);
		      SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)msg);
		      rc = mixerOpen(&hmx, i, (DWORD_PTR)hWnd, NULL, CALLBACK_WINDOW | MIXER_OBJECTF_MIXER);
		      if (rc != MMSYSERR_NOERROR) {
		        MessageBox(hWnd, TEXT("Error opening mixer deivce"), NULL, MB_OK);
			mixerClose(hmx);
		        continue;
		      }
		      lstrcpy(msg, TEXT("Type\tComponent\tName\tLine ID\tFlags\tCtls\tConnections"));
		      SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)msg);
		      MIXERLINE mxl;
		      for (uDest = 0; uDest < mxcaps.cDestinations; uDest++) {
			mxl.cbStruct = sizeof(mxl);
			mxl.dwDestination = uDest;
			rc = mixerGetLineInfo((HMIXEROBJ)hmx, &mxl, MIXER_GETLINEINFOF_DESTINATION);
			if (rc != MMSYSERR_NOERROR) {
			  wsprintf(msg, TEXT("mixerGetLineInfo(dst=%u) failed. rc=%u!"), uDest, rc);
			  MessageBox(hWnd, msg, NULL, MB_OK);
			  continue;
			}
			GetComponentType(&mxl, lpszComponent);
			wsprintf(msg, TEXT("%s\t%-25s\t%-25s\t%.08lXh\t%.08lXh\t%lu\t%lu"), 
			  (MIXERLINE_LINEF_ACTIVE & mxl.fdwLine) 
			    ? TEXT("Dest Active") : TEXT("Dest Inactive"),
			  lpszComponent, mxl.szName, mxl.dwLineID, mxl.fdwLine, mxl.cControls, mxl.cConnections);
			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)msg);
			uConnections = mxl.cConnections;
			for (uConnect = 0; uConnect < uConnections; uConnect++) {
			  mxl.cbStruct = sizeof(mxl);
			  mxl.dwDestination = uDest;
			  mxl.dwSource = uConnect;
			  rc = mixerGetLineInfo((HMIXEROBJ)hmx, &mxl, MIXER_GETLINEINFOF_SOURCE);
			  if (rc != MMSYSERR_NOERROR) {
			    wsprintf(msg, TEXT("mixerGetLineInfo(src=%u) failed. rc=%u!"), uConnect, rc);
			    MessageBox(hWnd, msg, NULL, MB_OK);
			    continue;
			  }
			  GetComponentType(&mxl, lpszComponent);
			  wsprintf(msg, TEXT("%s\t%-25s\t%-25s\t%.08lXh\t%.08lXh\t%lu\t%lu"), 
			    (MIXERLINE_LINEF_ACTIVE & mxl.fdwLine) 
			      ? TEXT("Src Active") : TEXT("Src Inactive"),
			    lpszComponent, mxl.szName, mxl.dwLineID, mxl.fdwLine, mxl.cControls, mxl.cConnections);
			  SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)msg);
			}
		        SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)TEXT(""));
		      }
		    }
		    break;
		  }
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
