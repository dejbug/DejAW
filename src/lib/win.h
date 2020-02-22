#pragma once
#include <windows.h>

namespace lib {
namespace win {

void init(WNDCLASSEX & wc, LPCSTR name=nullptr, WNDPROC callback=DefWindowProc) noexcept;

ATOM install(WNDCLASSEX const & wc) noexcept;

HWND create(WNDCLASSEX const & wc, LPCSTR title=nullptr) noexcept;

int run(HWND hwnd, HACCEL haccel) noexcept;

void closeWindow(HWND h) noexcept;

void move(HWND hwnd, int x, int y) noexcept;

void resize(HWND hwnd, int w, int h) noexcept;

void center(HWND hwnd) noexcept;

COLORREF setPenColor(HDC dc, COLORREF color) noexcept;

COLORREF setBrushColor(HDC dc, COLORREF color) noexcept;

struct Rect : RECT
{
	auto pos() const noexcept { return POINT{left, top}; }

	auto size() const noexcept { return SIZE{right-left, bottom-top}; }

	auto width() const noexcept { return right-left; }

	auto height() const noexcept { return bottom-top; }
};

struct WindowRect : Rect
{
	WindowRect(HWND hwnd) noexcept;
};

struct ClientRect : Rect
{
	ClientRect(HWND hwnd) noexcept;
};

} // !namespace win
} // !namespace lib
