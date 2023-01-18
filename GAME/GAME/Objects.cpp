#include "Objects.h"

#include <tchar.h>

void Circle(HDC hdc, int cx, int cy, int size) {
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, hPen);
	Ellipse(hdc, cx - size, cy - size, cx + size, cy + size);

	DeleteObject(hPen);
}
void RecursiveCircle(HDC hdc, int cx, int cy, int size) {
	Circle(hdc, cx, cy, size); // Circle() см лаб раб  11
	if (size < 10) {
		return;
	}
	RecursiveCircle(hdc, cx, cy - size, size / 2);
	RecursiveCircle(hdc, cx + size, cy, size / 2);
	RecursiveCircle(hdc, cx, cy + size, size / 2);
	RecursiveCircle(hdc, cx - size, cy, size / 2);
}


void DrawDefeatScreen(HDC hdc, int step) {
	long color = RGB((25 - step) * 10, (25 - step) * 10, (25 - step) * 10);
	RecursiveCircle(hdc, 450, 200, (step + 5) * 10);
}
void DrawVictoryScreen(HDC hdc, int step) {

}