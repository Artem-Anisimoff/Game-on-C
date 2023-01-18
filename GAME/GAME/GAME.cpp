// GAME.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "GAME.h"
#include <time.h>
#include <stdio.h>

#include "Objects.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна


int finish = 0;
int step = 0;
int lose = 0;


//координаты человечка
int ManX = 500;
int ManY = 300;


int ManHealth = 3;

int ManHasCross = 0;
//координаты ключа
//int KeyX = 300;
//int KeyY = 200;
#define NUM_KEYS 5
//x
int KeyX[NUM_KEYS] = { 100, 350, 250, 450, 850 };
//y
int KeyY[NUM_KEYS] = { 200, 70, 500, 500, 200 };

int KeyVisible[NUM_KEYS] = { 1, 1, 1, 1, 1 };

//координаты привидения

#define NUM_GHOST 5
//x
int GhostX[NUM_GHOST] = { 150, 200, 600, 300, 700 };
//y
int GhostY[NUM_GHOST] = { 300, 100, 400, 500, 100 };

int GhostVisible[NUM_GHOST] = { 1, 1, 1, 1, 1 };




#define NUM_CROSS 3

int CrossX[NUM_CROSS] = { 140, 500, 380 };
int CrossY[NUM_CROSS] = { 85, 85, 285 };

int CrossVisible[NUM_CROSS] = { 1, 1, 1 };


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//


//void Fon(HDC hdc, int x, int y) {
//    HPEN hPen;
//    HBRUSH hBrush;
//    RECT rect;
//    hBrush = CreateSolidBrush(RGB(190, 190, 190));
//    SelectObject(hdc, hBrush);
//    rect = { 0, 0, 1920, 1200 };
//    FillRect(hdc, &rect, hBrush);
//}

//
//
//void Circle(HDC hdc, int cx, int cy, int size) {
//	HPEN hPen;
//	hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//	SelectObject(hdc, hPen);
//	Ellipse(hdc, cx - size, cy - size, cx + size, cy + size);
//
//	DeleteObject(hPen);
//}
//void RecursiveCircle(HDC hdc, int cx, int cy, int size) {
//	Circle(hdc, cx, cy, size); // Circle() см лаб раб  11
//	if (size < 10) {
//		return;
//	}
//	RecursiveCircle(hdc, cx, cy - size, size / 2);
//	RecursiveCircle(hdc, cx + size, cy, size / 2);
//	RecursiveCircle(hdc, cx, cy + size, size / 2);
//	RecursiveCircle(hdc, cx - size, cy, size / 2);
//}
//
//
//void DrawDefeatScreen(HDC hdc, int step) {
//	long color = RGB((25 - step) * 10, (25 - step) * 10, (25 - step) * 10);
//	RecursiveCircle(hdc, 450, 200, (step + 5) * 10);
//}
//void DrawVictoryScreen(HDC hdc, int step) {
//
//}



//ФУНКЦИЯ GHOST

// x: - 60  Y: - 70 
void Ghost(HDC hdc, int x, int y) {
	//ghost
	HPEN hPen1;
	HPEN hPen2;
	HBRUSH hBrush1;
	HBRUSH hBrush2;
	hPen1 = CreatePen(PS_SOLID, 2, RGB(162, 162, 162));
	SelectObject(hdc, hPen1);
	hBrush1 = CreateSolidBrush(RGB(162, 162, 162));
	SelectObject(hdc, hBrush1);

	//туловище
	Ellipse(hdc, 20 - 60 + x, 20 - 70 + y, 100 - 60 + x, 100 - 70 + y);
	MoveToEx(hdc, 20 - 60 + x, 60 - 70 + y, NULL);
	LineTo(hdc, 20 - 60 + x, 110 - 70 + y);
	MoveToEx(hdc, 100 - 60 + x, 60 - 70 + y, NULL);
	LineTo(hdc, 100 - 60 + x, 110 - 70 + y);

	RECT rect = { 20 - 60 + x, 60 - 70 + y, 100 - 60 + x, 110 - 70 + y };
	FillRect(hdc, &rect, hBrush1);

	//низ
	Ellipse(hdc, 20 - 60 + x, 100 - 70 + y, 40 - 60 + x, 120 - 70 + y);
	Ellipse(hdc, 40 - 60 + x, 100 - 70 + y, 60 - 60 + x, 120 - 70 + y);
	Ellipse(hdc, 60 - 60 + x, 100 - 70 + y, 80 - 60 + x, 120 - 70 + y);
	Ellipse(hdc, 80 - 60 + x, 100 - 70 + y, 100 - 60 + x, 120 - 70 + y);

	//глаза
	hPen2 = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	SelectObject(hdc, hPen2);
	hBrush2 = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(hdc, hBrush2);

	Ellipse(hdc, 35 - 60 + x, 40 - 70 + y, 55 - 60 + x, 60 - 70 + y);
	Ellipse(hdc, 65 - 60 + x, 40 - 70 + y, 85 - 60 + x, 60 - 70 + y);



	DeleteObject(hPen1);
	DeleteObject(hPen2);
	DeleteObject(hBrush1);
	DeleteObject(hBrush2);
}




//ФУНКЦИЯ MAN
void Man(HDC hdc, int x, int y) {
	HPEN hPen3;
	HBRUSH hBrush3;
	HBRUSH hBrush4;
	HBRUSH hBrush5;
	HBRUSH hBrush6;
	HBRUSH hBrush7;
	RECT rect;

	//____________________________________________________
	//man
	// x: - 60   y: - 200

	hPen3 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hPen3);


	/*hBrush3 = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush3);*/
	//голова
	hBrush3 = CreateSolidBrush(RGB(255, 255, 120));
	SelectObject(hdc, hBrush3);

	Ellipse(hdc, 20 - 60 + x, 140 - 200 + y, 100 - 60 + x, 220 - 200 + y);

	//глаза
	hBrush4 = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush4);


	Ellipse(hdc, 40 - 60 + x, 160 - 200 + y, 60 - 60 + x, 180 - 200 + y);
	Ellipse(hdc, 60 - 60 + x, 160 - 200 + y, 80 - 60 + x, 180 - 200 + y);

	hBrush5 = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush5);
	Ellipse(hdc, 45 - 60 + x, 165 - 200 + y, 55 - 60 + x, 175 - 200 + y);
	Ellipse(hdc, 65 - 60 + x, 165 - 200 + y, 75 - 60 + x, 175 - 200 + y);

	//тело
	hBrush6 = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush6);
	rect = { 30 - 60 + x, 210 - 200 + y, 90 - 60 + x, 225 - 200 + y };
	FillRect(hdc, &rect, hBrush6);

	MoveToEx(hdc, 30 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 30 - 60 + x, 240 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 240 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 210 - 200 + y);
	LineTo(hdc, 30 - 60 + x, 210 - 200 + y);
	//руки


	MoveToEx(hdc, 30 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 20 - 60 + x, 220 - 200 + y);
	LineTo(hdc, 30 - 60 + x, 230 - 200 + y);

	MoveToEx(hdc, 90 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 100 - 60 + x, 220 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 230 - 200 + y);
	//ноги
	hBrush7 = CreateSolidBrush(RGB(139, 69, 19));
	SelectObject(hdc, hBrush7);
	rect = { 30 - 60 + x, 225 - 200 + y, 90 - 60 + x, 238 - 200 + y };
	FillRect(hdc, &rect, hBrush7);

	MoveToEx(hdc, 30 - 60 + x, 225 - 200 + y, NULL);
	LineTo(hdc, 90 - 60 + x, 225 - 200 + y);

	MoveToEx(hdc, 30 - 60 + x, 238 - 200 + y, NULL);
	LineTo(hdc, 90 - 60 + x, 238 - 200 + y);

	MoveToEx(hdc, 60 - 60 + x, 240 - 200 + y, NULL);
	LineTo(hdc, 60 - 60 + x, 230 - 200 + y);

	DeleteObject(hPen3);
	DeleteObject(hBrush3);
	DeleteObject(hBrush4);
	DeleteObject(hBrush5);
	DeleteObject(hBrush6);
	DeleteObject(hBrush7);

}

//MANWITHKEY
//ФУНКЦИЯ MAN
void ManWithKey(HDC hdc, int x, int y) {
	HPEN hPen;
	HBRUSH hBrush;
	RECT rect;
	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	//____________________________________________________
	//man
	// x: - 60   y: - 200
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	//голова
	hBrush = CreateSolidBrush(RGB(255, 255, 120));
	SelectObject(hdc, hBrush);

	Ellipse(hdc, 20 - 60 + x, 140 - 200 + y, 100 - 60 + x, 220 - 200 + y);

	//глаза
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);


	Ellipse(hdc, 40 - 60 + x, 160 - 200 + y, 60 - 60 + x, 180 - 200 + y);
	Ellipse(hdc, 60 - 60 + x, 160 - 200 + y, 80 - 60 + x, 180 - 200 + y);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hBrush);
	Ellipse(hdc, 45 - 60 + x, 165 - 200 + y, 55 - 60 + x, 175 - 200 + y);
	Ellipse(hdc, 65 - 60 + x, 165 - 200 + y, 75 - 60 + x, 175 - 200 + y);

	//тело
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	rect = { 30 - 60 + x, 210 - 200 + y, 90 - 60 + x, 225 - 200 + y };
	FillRect(hdc, &rect, hBrush);

	MoveToEx(hdc, 30 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 30 - 60 + x, 240 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 240 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 210 - 200 + y);
	LineTo(hdc, 30 - 60 + x, 210 - 200 + y);
	//руки


	MoveToEx(hdc, 30 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 20 - 60 + x, 220 - 200 + y);
	LineTo(hdc, 30 - 60 + x, 230 - 200 + y);

	MoveToEx(hdc, 90 - 60 + x, 210 - 200 + y, NULL);
	LineTo(hdc, 100 - 60 + x, 220 - 200 + y);
	LineTo(hdc, 90 - 60 + x, 230 - 200 + y);
	//ноги
	hBrush = CreateSolidBrush(RGB(139, 69, 19));
	SelectObject(hdc, hBrush);
	rect = { 30 - 60 + x, 225 - 200 + y, 90 - 60 + x, 238 - 200 + y };
	FillRect(hdc, &rect, hBrush);

	MoveToEx(hdc, 30 - 60 + x, 225 - 200 + y, NULL);
	LineTo(hdc, 90 - 60 + x, 225 - 200 + y);

	MoveToEx(hdc, 30 - 60 + x, 238 - 200 + y, NULL);
	LineTo(hdc, 90 - 60 + x, 238 - 200 + y);

	MoveToEx(hdc, 60 - 60 + x, 240 - 200 + y, NULL);
	LineTo(hdc, 60 - 60 + x, 230 - 200 + y);






	//key
	hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 175, 0));
	SelectObject(hdc, hPen);

	Ellipse(hdc, 100 - 70 + x, 210 - 200 + y, 120 - 70 + x, 230 - 200 + y);
	MoveToEx(hdc, 140 - 70 + x, 220 - 200 + y, NULL);
	LineTo(hdc, 140 - 70 + x, 230 - 200 + y);
	MoveToEx(hdc, 150 - 70 + x, 220 - 200 + y, NULL);
	LineTo(hdc, 150 - 70 + x, 230 - 200 + y);
	MoveToEx(hdc, 120 - 70 + x, 220 - 200 + y, NULL);
	LineTo(hdc, 160 - 70 + x, 220 - 200 + y);


	DeleteObject(hPen);
	DeleteObject(hBrush);

}

//DOOR
// x 230 ; y 180
void DOOR(HDC hdc, int x, int y) {
	HPEN hPen;
	HBRUSH hBrush;
	RECT rect;


	HBRUSH hBrushe = CreateSolidBrush(RGB(153, 76, 0));
	SelectObject(hdc, hBrushe);
	//rect = { 180 - 230 + x, 120 - 180 + y, 280 - 230 + x, 240 - 180 + y };
	//FillRect(hdc, &rect, hBrushe);
	Rectangle(hdc, 180 - 230 + x, 120 - 180 + y, 280 - 230 + x, 240 - 180 + y);

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hPen);

	MoveToEx(hdc, 180 - 230 + x, 120 - 180 + y, NULL);
	LineTo(hdc, 180 - 230 + x, 240 - 180 + y);
	LineTo(hdc, 280 - 230 + x, 240 - 180 + y);
	LineTo(hdc, 280 - 230 + x, 120 - 180 + y);
	LineTo(hdc, 180 - 230 + x, 120 - 180 + y);

	MoveToEx(hdc, 200 - 230 + x, 120 - 180 + y, NULL);
	LineTo(hdc, 200 - 230 + x, 240 - 180 + y);

	MoveToEx(hdc, 220 - 230 + x, 120 - 180 + y, NULL);
	LineTo(hdc, 220 - 230 + x, 240 - 180 + y);

	MoveToEx(hdc, 240 - 230 + x, 120 - 180 + y, NULL);
	LineTo(hdc, 240 - 230 + x, 240 - 180 + y);

	MoveToEx(hdc, 260 - 230 + x, 120 - 180 + y, NULL);
	LineTo(hdc, 260 - 230 + x, 240 - 180 + y);

	hBrush = CreateSolidBrush(RGB(255, 175, 0));
	SelectObject(hdc, hBrush);
	FillRect(hdc, &rect, hBrush);
	rect = { 265 - 230 + x, 125 - 180 + y, 275 - 230 + x, 135 - 180 + y };
	FillRect(hdc, &rect, hBrush);
	rect = { 265 - 230 + x, 145 - 180 + y, 275 - 230 + x, 155 - 180 + y };
	FillRect(hdc, &rect, hBrush);
	rect = { 265 - 230 + x, 165 - 180 + y, 275 - 230 + x, 175 - 180 + y };
	FillRect(hdc, &rect, hBrush);
	rect = { 265 - 230 + x, 185 - 180 + y, 275 - 230 + x, 195 - 180 + y };
	FillRect(hdc, &rect, hBrush);
	rect = { 265 - 230 + x, 205 - 180 + y, 275 - 230 + x, 215 - 180 + y };
	FillRect(hdc, &rect, hBrush);


	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(hBrushe);
}

//CROSS
void Cross(HDC hdc, int x, int y) {
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, hPen);


	MoveToEx(hdc, 260 - 260 + x, 20 - 50 + y, NULL);
	LineTo(hdc, 260 - 260 + x, 80 - 50 + y);
	MoveToEx(hdc, 240 - 260 + x, 40 - 50 + y, NULL);
	LineTo(hdc, 280 - 260 + x, 40 - 50 + y);

	DeleteObject(hPen);
}

void DrawCross(HDC hdc) {
	for (int i = 0; i < NUM_CROSS; i++) {
		if (CrossVisible[i]) {
			Cross(hdc, CrossX[i], CrossY[i]);
		}
	}
}

void TryToTakeCross() {

	if (!ManHasCross) {

		for (int i = 0; i < NUM_CROSS; i++) {

			if (CrossVisible[i]) {

				if (CrossX[i] - 20 < ManX
					&& CrossX[i] + 20 > ManX
					&& CrossY[i] - 20 < ManY
					&& CrossY[i] + 20 > ManY) {

					CrossVisible[i] = 0;

					ManHasCross = 1;

					return;
				}
			}
		}
	}
}

void ContactManAndGHost() {

	for (int i = 0; i < NUM_GHOST; i++) {

		if (GhostVisible[i]) {

			if (ManX - 50 < GhostX[i]
				&& ManX + 50 > GhostX[i]
				&& ManY - 50 < GhostY[i]
				&& ManY + 50 > GhostY[i]) {

				if (ManHasCross) {

					GhostVisible[i] = 0;

					ManHasCross = 0;
				}

				else {

					ManHealth--;
				}
			}
		}
	}
}

//________________________________________________
//KEY
// x: - 190  y: - 50
void Key(HDC hdc, int x, int y) {

	HPEN hPen;
	HBRUSH hBrush;
	RECT rect;
	hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 255));
	SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 175, 0));
	SelectObject(hdc, hPen);

	Ellipse(hdc, 160 - 190 + x, 40 - 50 + y, 180 - 190 + x, 60 - 50 + y);
	MoveToEx(hdc, 200 - 190 + x, 50 - 50 + y, NULL);
	LineTo(hdc, 200 - 190 + x, 60 - 50 + y);
	MoveToEx(hdc, 210 - 190 + x, 50 - 50 + y, NULL);
	LineTo(hdc, 210 - 190 + x, 60 - 50 + y);
	MoveToEx(hdc, 180 - 190 + x, 50 - 50 + y, NULL);
	LineTo(hdc, 220 - 190 + x, 50 - 50 + y);
	DeleteObject(hPen);
	DeleteObject(hBrush);

}
int CountVisibleKeys() {

	int count = 0;
	int i = 0;
	do {

		if (KeyVisible[i]) {
			++count;
		}

		++i;
	} while (i < NUM_KEYS);

	return count;
}

int CountVisibleGhost() {

	int count = 0;
	int i = 0;
	do {

		if (GhostVisible[i]) {
			++count;
		}

		++i;
	} while (i < NUM_GHOST);

	return count;
}

//int KeyPickUp() {
//
//    if (ManX - 20 < KeyX
//        && ManX + 20 > KeyX
//        && ManY - 20 < KeyY
//        && ManY + 20 > KeyY) {
//
//        return 1;
//    }
//    else {
//        return 0;
//    }
//}
void TryToKeyPickUp() {

	int i = 0;
	do {

		if (KeyVisible[i]) {

			if (ManX - 40 < KeyX[i]
				&& ManX + 40 > KeyX[i]
				&& ManY - 40 < KeyY[i]
				&& ManY + 40 > KeyY[i]) {

				KeyVisible[i] = 0;
			}
		}

		++i;
	} while (i < NUM_KEYS);
}

//случайное перемещение приведения
void RandomMoveGhost() {

	int i = 0;
	do {

		if (GhostVisible[i]) {

			int dx = rand() % 81 - 40;
			int dy = rand() % 81 - 40;

			GhostX[i] += dx;
			GhostY[i] += dy;

		}
		++i;
	} while (i < NUM_GHOST);
}


void TryToEatMan() {
	int i = 0;
	do {
		if (GhostVisible[i]) {

			if (ManX - 40 < GhostX[i]
				&& ManX + 40 > GhostX[i]
				&& ManY - 40 < GhostY[i]
				&& ManY + 40 > GhostY[i]) {

				ManHealth--;

			}
		}
		++i;
	} while (i < NUM_GHOST);
}

void DrawKeys(HDC hdc) {

	int i = 0;
	do {

		if (KeyVisible[i]) {
			Key(hdc, KeyX[i], KeyY[i]);
		}
		++i;
	} while (i < NUM_KEYS);
}

void DrawGhosts(HDC hdc) {

	int i = 0;
	do {

		if (GhostVisible[i]) {
			Ghost(hdc, GhostX[i], GhostY[i]);
		}
		++i;
	} while (i < NUM_GHOST);
}

void DrawFinalScreen(HDC hdc) {
	HBRUSH hBrushEmptyCell; //создаём кисть для пустого поля
	hBrushEmptyCell = CreateSolidBrush(RGB(255, 255, 255)); // серый
	RECT rect = { 0, 0,  600, 720 };
	FillRect(hdc, &rect, hBrushEmptyCell);

	HFONT hFont;
	hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Courier New");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 0, 0));

	TCHAR  string1[] = _T("Победа!");
	TextOut(hdc, 200, 300, (LPCWSTR)string1, _tcslen(string1));
}

void DrawLoseScreen(HDC hdc) {
	HBRUSH hBrushEmptyCell; //создаём кисть для пустого поля
	hBrushEmptyCell = CreateSolidBrush(RGB(255, 255, 255)); // серый
	RECT rect = { 0, 0,  600, 720 };
	FillRect(hdc, &rect, hBrushEmptyCell);

	HFONT hFont;
	hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"Courier New");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(255, 0, 0));

	TCHAR  string1[] = _T("Поражение");
	TextOut(hdc, 200, 300, (LPCWSTR)string1, _tcslen(string1));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	//сообщение о создании окна
	case WM_CREATE:

		srand(time(NULL));

		SetTimer(hWnd, 1, 500, NULL);

		break;
		//таймер сработал
	case WM_TIMER:


		
	



		RandomMoveGhost();

		TryToEatMan();
		if (ManHealth == 0) {
			PostQuitMessage(0);
		}

		ContactManAndGHost();
		if (ManHealth == 0) {
			PostQuitMessage(0);
		}


		InvalidateRect(hWnd, NULL, TRUE);

		break;


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			ManY -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			ManY += 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case VK_LEFT:
			ManX -= 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			ManX += 10;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		TryToKeyPickUp();
		if (CountVisibleKeys() == 0) {
			//PostQuitMessage(0);
			finish = 1;
		
		}

		TryToTakeCross();

		ContactManAndGHost();
		if (ManHealth == 0) {
			//PostQuitMessage(0);
			lose = 1;
		}





		break;


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...

	   // Fon(hdc, 0, 0);

		//Ghost(hdc, GhostX, GhostY);
		//Ghost(hdc, 50, 120);
		//Ghost(hdc, 120, 500);
		//Ghost(hdc, 330, 110);
		//Ghost(hdc, 800, 750);


		//DOOR(hdc, 100, 100);





		//Key(hdc, 300, 400);



		if (finish == 1) {
			DrawFinalScreen(hdc);
		}
		else if (lose ==1) {
			DrawLoseScreen(hdc);
		}
		else {
			DrawGhosts(hdc);
			Man(hdc, ManX, ManY);
			DrawKeys(hdc);
			DrawCross(hdc);
		}
		//ManWithKey(hdc, 100, 100);
		/*if (finish) {

			if (!winner) {
				if (!winner) {
					DrawDefeatScreen(hdc, step);
				}
				else {
					DrawVictoryScreen(hdc, step);
				}
			}
			if (step > 20) {
				DrawFinalScreen(hdc);
			}
		}
		else {
			DrawGhosts(hdc);
			Man(hdc, ManX, ManY);
			DrawKeys(hdc);
			DrawCross(hdc);
		}*/




		EndPaint(hWnd, &ps);
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






// Обработчик сообщений для окна "О программе".
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
