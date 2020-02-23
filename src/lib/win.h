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

HGDIOBJ selectStockObject(HDC dc, int id) noexcept;

// COLORREF setPenColor(HDC dc, COLORREF color) noexcept;

// COLORREF setBrushColor(HDC dc, COLORREF color) noexcept;

void whiteness(HDC dc, int x, int y, int w, int h, bool invert=false) noexcept;

} // !namespace win
} // !namespace lib
