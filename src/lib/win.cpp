#include "win.h"

COLORREF lib::win::setPenColor(HDC dc, COLORREF color)
{
	SelectObject(dc, GetStockObject(DC_PEN));
	return SetDCPenColor(dc, color);
}

COLORREF lib::win::setBrushColor(HDC dc, COLORREF color)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	return SetDCBrushColor(dc, color);
}
