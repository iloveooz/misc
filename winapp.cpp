#include <windows.h>
#include <tchar.h>		// содержит полезные макросы для поддержки Unicode

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);		// прототип оконной функции

TCHAR WinName[] = _T("MainFrame");

	// Дескриптор текущего приложения
	// В современных системах всегда 0
	// Командная строка
	// Режим отображения окна
int APIENTRY _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode) {

	HWND hWnd;		// Дескриптор главного окна программы
	MSG msg;		// Структура для хранения сообщения
	WNDCLASS wc;	// Класс окна, настройка окна

	// Определение класса окна
	wc.hInstance = This;								// дескриптор, присваеваемый ОС при загрузке приложения
	wc.lpszClassName = WinName;							// Имя класса окна
	wc.lpfnWndProc = WndProc;							// Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW;					// Стиль окна, автоматическая прорисовка окна
	wc.hIcon = LoadIcon(NULL, IDI_QUESTION);	// Стандартная иконка
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);	// Стандартный курсор
	wc.lpszMenuName = NULL;								// Нет меню
	wc.cbClsExtra = 0;									// Нет дополнительных данных класса
	wc.cbWndExtra = 0;									// Нет дополнительных данных окна
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// Заполнение окна белым цветом

	if (!RegisterClass(&wc)) 
		return 0; // Регистрация класса окна

	// Создание окна
	hWnd = CreateWindow(WinName,		// Имя класса окна
	_T("Каркас Windows-приложения"),	// Заголовок окна
	WS_OVERLAPPEDWINDOW,				// Стиль окна
	CW_USEDEFAULT,						// x
	CW_USEDEFAULT,						// y Размеры окна
	CW_USEDEFAULT,						// Width
	CW_USEDEFAULT,						// Height
	HWND_DESKTOP,						// Дескриптор родительского окна
	NULL,								// Нет меню
	This,								// Дескриптор приложения
	NULL);								// Дополнительной информации нет

	ShowWindow(hWnd, mode); //Показать окно

	// Цикл обработки сообщений
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg); // Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);  // Посылает сообщение функции WndProc()
	}
	return 0;
	}

// Оконная функция вызывается операционной системой и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)	{ 
	// Обработчик сообщений
	switch(message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break; // Завершение программы
		// Обработка сообщения по умолчанию
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
