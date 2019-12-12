// winapi_child_windows.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winapi_child_windows.h"

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

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI_CHILD_WINDOWS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI_CHILD_WINDOWS));

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
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI_CHILD_WINDOWS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINAPI_CHILD_WINDOWS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
TCHAR ChildClassName[MAX_LOADSTRING] = _T("WinChild");

ATOM MyRegisterChildClass() {

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = ChildProc;
	wcex.hInstance = hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = ChildClassName;

	return RegisterClassEx(&wcex);
}

static HFONT newFont;
static HWND hChild[9];

unsigned char k[9] = { 0 };
char text[] = { ' ', 'X', '0' };

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
	int i;
	static int sx, sy;
	switch (message) {
		case WM_CREATE:
			MyRegisterChildClass();
			for (i = 0; i < 9; i++)
				hChild[i] = CreateWindow(ChildClassName, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		break;

		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED) 
				break; //Кнопка свертывания окна
			sx = LOWORD(lParam) / 3; //Ширина дочернего окна
			sy = HIWORD(lParam) / 3; //Высота дочернего окна

			if (newFont) 
				DeleteObject(newFont);
			
			newFont = CreateFont(
				min(sx, sy), 0, 0, 0, FW_NORMAL, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));

			for (i = 0; i < 9; i++) {
				MoveWindow(hChild[i],(i % 3) * sx, (i / 3) * sy, sx, sy, TRUE);
				UpdateWindow(hChild[i]);
			}
		break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_FILE_NEW:
					for (i = 0; i < 9; i++) {
						k[i] = 0;
						InvalidateRect(hChild[i], NULL, 1);
						UpdateWindow(hChild[i]);
					}
				break;

				case IDM_EXIT: 
					DestroyWindow(hWnd); 
				break;

				default: 
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		break;

		case WM_DESTROY: 
			PostQuitMessage(0); 
		break;

		default: 
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	int i, s;
	char *ch;

	switch (message) {
		case WM_LBUTTONDOWN :
			for (i = 0; hWnd != hChild[i]; i++);

			if (k[i]) 
				break; 
			else 
				k[i] = 1;

			InvalidateRect(hWnd, NULL, 1);
			UpdateWindow(hWnd);
			
			srand(lParam);
			
			for(i = s = 0; i < 9; i++) 
				if (k[i]) 
					s++;
			if (s == 9) 
				MessageBox(hWnd, _T("Для следующего сеанса выбирайте 	New"), _T("Конец игры"), MB_OK | MB_ICONQUESTION);
			else {
				while(true) {
					s = rand() * 9 / (RAND_MAX + 1);
				if (k[s]) 
					continue;
				k[s] = 2;

				InvalidateRect(hChild[s], NULL, 1);
				UpdateWindow(hChild[s]);
				break;
				}
			}
		break;

		case WM_PAINT:
			for (i = 0; hWnd != hChild[i]; i++);
			if (k[i]) {
				ch = text + k[i];
				hdc = BeginPaint(hWnd, &ps);
				GetClientRect(hWnd, &rt);
				SelectObject(hdc, newFont);
				DrawTextA(hdc,ch,1,&rt,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
				EndPaint(hWnd, &ps);
			} //Фоновая закраска окна
			else 
				DefWindowProc(hWnd, message, wParam, lParam);
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
