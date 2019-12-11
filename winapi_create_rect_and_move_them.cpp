// winapi_chess_map.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winapi_chess_map.h"

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
	LoadString(hInstance, IDC_WINAPI_CHESS_MAP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI_CHESS_MAP));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI_CHESS_MAP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINAPI_CHESS_MAP);
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
	HDC hdc;                 // device context (DC) for window  
    RECT rcTmp;              // temporary rectangle  
    PAINTSTRUCT ps;          // paint data for BeginPaint and EndPaint  
    POINT ptClientUL;        // client area upper left corner  
    POINT ptClientLR;        // client area lower right corner  
    static HDC hdcCompat;    // DC for copying bitmap  
    static POINT pt;         // x and y coordinates of cursor  
    static RECT rcBmp;       // rectangle that encloses bitmap  
    static RECT rcTarget;    // rectangle to receive bitmap  
    static RECT rcClient;    // client-area rectangle  
    static BOOL fDragRect;   // TRUE if bitmap rect. is dragged  
    static HBITMAP hbmp;     // handle of bitmap to display  
    static HBRUSH hbrBkgnd;  // handle of background-color brush  
    static COLORREF crBkgnd; // color of client-area background  
    static HPEN hpenDot;     // handle of dotted pen  
 
    switch (message) 
    { 
        case WM_CREATE: 
 
            // Load the bitmap resource.  
 
           // hbmp = LoadBitmap(hinst, MAKEINTRESOURCE(1)); 
 
            // Create a device context (DC) to hold the bitmap.  
            // The bitmap is copied from this DC to the window's DC  
            // whenever it must be drawn.  
 
            hdc = GetDC(hWnd); 
            hdcCompat = CreateCompatibleDC(hdc); 
            SelectObject(hdcCompat, hbmp); 
 
            // Create a brush of the same color as the background  
            // of the client area. The brush is used later to erase  
            // the old bitmap before copying the bitmap into the  
            // target rectangle.  
 
            crBkgnd = GetBkColor(hdc); 
            hbrBkgnd = CreateSolidBrush(crBkgnd); 
            ReleaseDC(hWnd, hdc); 
 
            // Create a dotted pen. The pen is used to draw the  
            // bitmap rectangle as the user drags it.  
 
            hpenDot = CreatePen(PS_DOT, 1, RGB(0, 0, 0)); 
 
            // Set the initial rectangle for the bitmap. Note that  
            // this application supports only a 32- by 32-pixel  
            // bitmap. The rectangle is slightly larger than the  
            // bitmap.  
 
            SetRect(&rcBmp, 1, 1, 34, 34); 
            return 0; 
 
        case WM_PAINT: 
 
            // Draw the bitmap rectangle and copy the bitmap into  
            // it. The 32-pixel by 32-pixel bitmap is centered  
            // in the rectangle by adding 1 to the left and top  
            // coordinates of the bitmap rectangle, and subtracting 2  
            // from the right and bottom coordinates.  
 
            BeginPaint(hWnd, &ps); 
            Rectangle(ps.hdc, rcBmp.left, rcBmp.top, 
                rcBmp.right, rcBmp.bottom); 
            StretchBlt(ps.hdc, rcBmp.left + 1, rcBmp.top + 1, 
                (rcBmp.right - rcBmp.left) - 2, 
                (rcBmp.bottom - rcBmp.top) - 2, hdcCompat, 
                0, 0, 32, 32, SRCCOPY); 
            EndPaint(hWnd, &ps); 
            break; 
 
        case WM_MOVE: 
        case WM_SIZE: 
 
            // Convert the client coordinates of the client-area  
            // rectangle to screen coordinates and save them in a  
            // rectangle. The rectangle is passed to the ClipCursor  
            // function during WM_LBUTTONDOWN processing.  
 
            GetClientRect(hWnd, &rcClient); 
            ptClientUL.x = rcClient.left; 
            ptClientUL.y = rcClient.top; 
            ptClientLR.x = rcClient.right; 
            ptClientLR.y = rcClient.bottom; 
            ClientToScreen(hWnd, &ptClientUL); 
            ClientToScreen(hWnd, &ptClientLR); 
            SetRect(&rcClient, ptClientUL.x, ptClientUL.y, 
                ptClientLR.x, ptClientLR.y); 
            return 0; 
 
        case WM_LBUTTONDOWN: 
 
            // Restrict the mouse cursor to the client area. This  
            // ensures that the window receives a matching  
            // WM_LBUTTONUP message.  
 
            ClipCursor(&rcClient); 
 
            // Save the coordinates of the mouse cursor.  
 
            pt.x = (LONG) LOWORD(lParam); 
            pt.y = (LONG) HIWORD(lParam); 
 
            // If the user has clicked the bitmap rectangle, redraw  
            // it using the dotted pen. Set the fDragRect flag to  
            // indicate that the user is about to drag the rectangle.  
 
            if (PtInRect(&rcBmp, pt)) 
            { 
                hdc = GetDC(hWnd); 
                SelectObject(hdc, hpenDot); 
                Rectangle(hdc, rcBmp.left, rcBmp.top, rcBmp.right, 
                    rcBmp.bottom); 
                fDragRect = TRUE; 
                ReleaseDC(hWnd, hdc); 
            } 
            return 0; 
 
        case WM_MOUSEMOVE: 
 
            // Draw a target rectangle or drag the bitmap rectangle,  
            // depending on the status of the fDragRect flag.  
 
            if ((wParam && MK_LBUTTON) 
                    && !fDragRect) 
            {
                // Set the mix mode so that the pen color is the  
                // inverse of the background color. The previous  
                // rectangle can then be erased by drawing  
                // another rectangle on top of it.  
 
                hdc = GetDC(hWnd); 
                SetROP2(hdc, R2_NOTXORPEN); 
 
                // If a previous target rectangle exists, erase  
                // it by drawing another rectangle on top of it.  
 
                if (!IsRectEmpty(&rcTarget)) 
                { 
                    Rectangle(hdc, rcTarget.left, rcTarget.top, 
                        rcTarget.right, rcTarget.bottom); 
                } 
 
                // Save the coordinates of the target rectangle. Avoid  
                // invalid rectangles by ensuring that the value of  
                // the left coordinate is lesser than the  
                // right coordinate, and that the value of the top 
                // coordinate is lesser than the bottom coordinate. 
 
                if ((pt.x < (LONG) LOWORD(lParam)) && 
                        (pt.y > (LONG) HIWORD(lParam))) 
                {
                    SetRect(&rcTarget, pt.x, HIWORD(lParam), 
                        LOWORD(lParam), pt.y); 
                }
                else if ((pt.x > (LONG) LOWORD(lParam)) && 
                        (pt.y > (LONG) HIWORD(lParam))) 
                {
                    SetRect(&rcTarget, LOWORD(lParam), 
                        HIWORD(lParam), pt.x, pt.y); 
                }
                else if ((pt.x > (LONG) LOWORD(lParam)) && 
                        (pt.y < (LONG) HIWORD(lParam))) 
                { 
                    SetRect(&rcTarget, LOWORD(lParam), pt.y, 
                        pt.x, HIWORD(lParam)); 
                }
                else 
                {
                    SetRect(&rcTarget, pt.x, pt.y, LOWORD(lParam), 
                        HIWORD(lParam)); 
                }
 
                // Draw the new target rectangle.  
 
                Rectangle(hdc, rcTarget.left, rcTarget.top, 
                    rcTarget.right, rcTarget.bottom); 
                ReleaseDC(hWnd, hdc); 
            } 
            else if ((wParam && MK_LBUTTON) 
                    && fDragRect) 
            {
 
                // Set the mix mode so that the pen color is the  
                // inverse of the background color.  
 
                hdc = GetDC(hWnd); 
                SetROP2(hdc, R2_NOTXORPEN); 
 
                // Select the dotted pen into the DC and erase  
                // the previous bitmap rectangle by drawing  
                // another rectangle on top of it.  
 
                SelectObject(hdc, hpenDot); 
                Rectangle(hdc, rcBmp.left, rcBmp.top, 
                    rcBmp.right, rcBmp.bottom); 
 
                // Set the new coordinates of the bitmap rectangle,  
                // then redraw it.  
 
                OffsetRect(&rcBmp, LOWORD(lParam) - pt.x, 
                    HIWORD(lParam) - pt.y); 
                Rectangle(hdc, rcBmp.left, rcBmp.top, 
                    rcBmp.right, rcBmp.bottom); 
                ReleaseDC(hWnd, hdc); 
 
                // Save the coordinates of the mouse cursor.  
 
                pt.x = (LONG) LOWORD(lParam); 
                pt.y = (LONG) HIWORD(lParam); 
            } 
            return 0; 
 
        case WM_LBUTTONUP: 
 
            // If the bitmap rectangle and target rectangle  
            // intersect, copy the bitmap into the target  
            // rectangle. Otherwise, copy the bitmap into the  
            // rectangle bitmap at its new location.  
 
            if (IntersectRect(&rcTmp, &rcBmp, &rcTarget)) 
            { 
 
                // Erase the bitmap rectangle by filling it with  
                // the background color.  
 
                hdc = GetDC(hWnd); 
                FillRect(hdc, &rcBmp, hbrBkgnd); 
 
                // Redraw the target rectangle because the part  
                // that intersected with the bitmap rectangle was  
                // erased by the call to FillRect.  
 
                Rectangle(hdc, rcTarget.left, rcTarget.top, 
                    rcTarget.right, rcTarget.bottom); 
 
                // Copy the bitmap into the target rectangle.  
 
                StretchBlt(hdc, rcTarget.left + 1, rcTarget.top + 1, 
                    (rcTarget.right - rcTarget.left) - 2, 
                    (rcTarget.bottom - rcTarget.top) - 2, hdcCompat, 
                    0, 0, 32, 32, SRCCOPY); 
 
                // Copy the target rectangle to the bitmap  
                // rectangle, set the coordinates of the target  
                // rectangle to 0, then reset the fDragRect flag.  
 
                CopyRect(&rcBmp, &rcTarget); 
                SetRectEmpty(&rcTarget); 
                ReleaseDC(hWnd, hdc); 
                fDragRect = FALSE; 
            } 
 
            else if (fDragRect) 
            { 
 
                // Draw the bitmap rectangle, copy the bitmap into  
                // it, and reset the fDragRect flag.  
 
                hdc = GetDC(hWnd); 
                Rectangle(hdc, rcBmp.left, rcBmp.top, 
                    rcBmp.right, rcBmp.bottom); 
                StretchBlt(hdc, rcBmp.left + 1, rcBmp.top + 1, 
                    (rcBmp.right - rcBmp.left) - 2, 
                    (rcBmp.bottom - rcBmp.top) - 2, hdcCompat, 
                    0, 0, 32, 32, SRCCOPY); 
                ReleaseDC(hWnd, hdc); 
                fDragRect = FALSE; 
            } 
 
            // Release the mouse cursor.  
 
            ClipCursor((LPRECT) NULL); 
            return 0; 
 
        case WM_DESTROY: 
 
            // Destroy the background brush, compatible bitmap,  
            // and the bitmap.  
 
            DeleteObject(hbrBkgnd); 
            DeleteDC(hdcCompat); 
            DeleteObject(hbmp); 
            PostQuitMessage(0); 
            break; 
 
        default: 
            return DefWindowProc(hWnd, message, wParam, lParam); 
    } 
    return (LRESULT) NULL; 
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
