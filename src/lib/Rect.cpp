#include "Rect.h"


lib::WindowRect::WindowRect(HWND hwnd) noexcept
{
	if (hwnd)
		GetWindowRect(hwnd, this);
	else
	{
		left = top = 0;
		right = GetSystemMetrics(SM_CXSCREEN);
		bottom = GetSystemMetrics(SM_CYSCREEN);
	}
}


lib::ClientRect::ClientRect(HWND hwnd) noexcept
{
	if (hwnd)
		GetClientRect(hwnd, this);
	else
	{
		left = top = 0;
		right = GetSystemMetrics(SM_CXSCREEN);
		bottom = GetSystemMetrics(SM_CYSCREEN);
	}
}
