#include "Dc.h"

Dc::Dc(HDC handle) : handle(handle)
{
}

Dc Dc::for_client(HWND h)
{
	Dc dc;
	dc.handle = GetDC(h);
	return dc;
}

void Dc::set_pen_color(COLORREF c)
{
	SelectObject(handle, GetStockObject(DC_PEN));
	SetDCPenColor(handle, c);
}

void Dc::set_brush_color(COLORREF c)
{
	SelectObject(handle, GetStockObject(DC_BRUSH));
	SetDCBrushColor(handle, c);
}

void Dc::draw_line(HDC dc, POINT a, POINT b)
{
	MoveToEx(dc, a.x, a.y, nullptr);
	LineTo(dc, b.x, b.y);
}

void Dc::draw_line(POINT a, POINT b)
{
	draw_line(handle, a, b);
}
