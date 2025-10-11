#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>	//Функции написаны на языке 'C'
//#include<сstdio>	//Функции написаны на языке 'C++'
#include"resource.h"

CONST CHAR g_sz_WND_CLASS_NAME[] = "My Windows Class";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;	//Структура, описывающая класс окна
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "Bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIcon = (HICON)LoadImage(hInstance, "2Palms.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Working In Background.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WND_CLASS_NAME;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:

	//https://stackoverflow.com/questions/4631292/how-to-detect-the-current-screen-resolution
	//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics
	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);

	INT window_width = screen_width / 4 * 3;
	INT window_height = screen_height * .75;

	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyles
		g_sz_WND_CLASS_NAME,	//Class name
		g_sz_WND_CLASS_NAME,	//Winodw title
		WS_OVERLAPPEDWINDOW,
		window_start_x, window_start_y,	//Window position
		window_width, window_height,	//Window size
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот Static-text создан при помощи функции CreateWindowEx();",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			500, 25,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),
			NULL
		);
		//WS_ - WindowStyle
		//ES_ - EditControl Style
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 45,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE,
			430, 70,
			80, 32,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
		//WS_CHILD - показывает, что создаваемое окно является дочерним элементом интерфейса какого-то другого окна
	}
	break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT wnd_rect;
		GetWindowRect(hwnd, &wnd_rect);
		CHAR sz_title[256] = {};
		sprintf
		(
			sz_title, "%s Position: %ix%i, Size:%ix%i", 
			g_sz_WND_CLASS_NAME, 
			wnd_rect.left, wnd_rect.top,
			wnd_rect.right-wnd_rect.left,
			wnd_rect.bottom - wnd_rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			MessageBox(hwnd, "Привет", "Привет", MB_OK | MB_ICONINFORMATION);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);

			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd,1002), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "Лучше двери закройте...", "Finita la comedia", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		//DestroyWindow(hwnd);
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Че, внатуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
			SendMessage(hwnd, WM_DESTROY, 0, 0);
		//Гатова
		break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}