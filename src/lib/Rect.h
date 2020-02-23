#pragma once
#include <windows.h>

namespace lib {


struct Rect : RECT
{
	operator LPRECT() { return this; }

	auto point() const noexcept { return POINT{left, top}; }

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


} // !lib
