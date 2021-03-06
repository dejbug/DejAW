#pragma once
#include <windows.h>

namespace dejlib3 {
namespace win {
namespace def {

constexpr DWORD frame_xstyle =
		WS_EX_OVERLAPPEDWINDOW|WS_EX_ACCEPTFILES|
		WS_EX_CONTEXTHELP|WS_EX_CONTROLPARENT;

constexpr DWORD frame_style =
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN;

} // :: def

int run(HWND=NULL, HACCEL=NULL);

HWND create_window(LPCSTR cname, HWND parent, UINT id,
		DWORD style=0, DWORD xstyle=0);

HWND create_window(LPCSTR cname,
		DWORD style=0, DWORD xstyle=0);

void close_window(HWND);

void repaint_window(HWND);

void get_client_size(HWND, SIZE &);

struct Dc
{
	HDC handle = nullptr;
	
	Dc(HDC=nullptr);

	static Dc for_client(HWND);

	void set_pen_color(COLORREF c);
	void set_brush_color(COLORREF c);
};

struct PaintDc : public Dc
{
	PAINTSTRUCT ps;

	PaintDc(HWND);
	PaintDc(HWND, COLORREF p, COLORREF b=0);
	virtual ~PaintDc();
};

void draw_line(HDC, POINT a, POINT b);

inline void draw_line(Dc const & dc, POINT a, POINT b)
{
	draw_line(dc.handle, a, b);
}

} // :: win
} // :: dejlib3
