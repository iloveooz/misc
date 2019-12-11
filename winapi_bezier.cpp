// winapi_sinusoid.cpp : Defines the entry point for the application.

#include "stdafx.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "regions.h"
#include <fstream>

#define MAX_LOADSTRING 100

static int sx, sy;
const int SCALE = 1000;
const int MARK = 4;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_REGIONS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REGIONS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

//  PURPOSE: Registers the window class.
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDC_REGIONS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_REGIONS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//   PURPOSE: Saves instance handle and creates main window
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//  PURPOSE:  Processes messages for the main window.
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return

void DcInLp(POINT &point) {
	point.x = point.x * SCALE / sx;
	point.y = SCALE - point.y * SCALE / sy;
}

void transform(HDC& hdc) {
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, SCALE, -SCALE, NULL);
	SetViewportExtEx(hdc, sx, sy, NULL);
	SetViewportOrgEx(hdc, 0, sy, NULL);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;

	static HPEN hDash, hBezier;
	static HBRUSH hRect, hSel;
	static POINT pt[20];
	static POINT point;
	
	RECT rt;
	
	static int count, index;
	static bool capture;
	int i;
	
	std::ifstream in;
	std::ofstream out;
	
	switch (message)
	{
	case WM_CREATE:
	in.open("dat.txt");
	if (in.fail())
	{
	MessageBox(hWnd,_T("Файл dat.txt не найден"),
	_T("Открытие файла"), MB_OK | MB_ICONEXCLAMATION);
	PostQuitMessage(0);
	return 1;
	}

	for (count = 0; in >> pt[count].x; count++) in >> pt[count].y;
	in.close(); //В переменной count сохранится размер массива точек
	hDash = CreatePen(PS_DASH, 1, 0);
	hBezier = CreatePen(PS_SOLID, 4, RGB(128, 0, 255));
	hRect = CreateSolidBrush(RGB(128, 0, 128));
	hSel = CreateSolidBrush(RGB(255, 0, 0));
	break;
	case WM_SIZE:
	sx = LOWORD(lParam);
	sy = HIWORD(lParam);
	break;
	case WM_LBUTTONDOWN:
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	//Преобразование экранных координат мыши в логические
	DcInLp(point);
	for (i = 0; i < count; i++)
	{
	SetRect(&rt,pt[i].x-MARK,pt[i].y-	MARK,pt[i].x+MARK,pt[i].y+MARK);
	if (PtInRect(&rt, point))
	{ //Курсор мыши попал в точку
	index = i;
	capture = true;
	hdc = GetDC(hWnd);
	transform(hdc); //Переход в логические координаты
	FillRect(hdc, &rt, hSel);//Отметим прямоугольник цветом
	ReleaseDC(hWnd, hdc);
	SetCapture(hWnd); //Захват мыши
	return 0;
	}
	}
	break;
	case WM_LBUTTONUP:
	if (capture)
	{
	ReleaseCapture(); //Освобождение мыши
	capture = false;
	}
	break;
	case WM_MOUSEMOVE:
	if (capture)
	{ //Мышь захвачена
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	DcInLp(point); //Преобразование экранных координат мыши
	pt[index] = point; //в логические координаты
	InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);
	transform(hdc); //Переход в логические координаты
	SelectObject(hdc, hDash);
	Polyline(hdc, pt, count); //Строим ломаную линию
	SelectObject(hdc, hBezier);
	PolyBezier(hdc, pt, count); //Строим кривую Безье
	for (i = 0; i < count; i++)
	{ //Закрашиваем точки графика прямоугольниками
	SetRect(&rt,pt[i].x-MARK,pt[i].y-MARK,pt[i].
	x+MARK,pt[i].y+MARK);
	FillRect(hdc, &rt, hRect);
	}
	EndPaint(hWnd, &ps);
	break;
	case WM_DESTROY:
	DeleteObject(hDash);
	DeleteObject(hBezier);
	DeleteObject(hRect);
	DeleteObject(hSel);
	out.open("dat.txt");
	for (i = 0;i<count;i++) out << pt[i].x << '\t' << pt[i].y << '\n';
	out.close();
	PostQuitMessage(0);
	break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
