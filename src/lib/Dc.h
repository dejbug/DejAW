#pragma once
#include <windows.h>

struct Dc
{
	HDC handle { nullptr };

	Dc(HDC=nullptr);

	static Dc for_client(HWND);

	void set_pen_color(COLORREF c);
	void set_brush_color(COLORREF c);

	void draw_line(POINT a, POINT b);

	static void draw_line(HDC dc, POINT a, POINT b);
};
