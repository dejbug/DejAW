#pragma once
#include <windows.h>


template<typename T>
struct Handle;


template<>
struct Handle<HDC>
{
	HDC const handle;
	bool const owned;

	static auto CreateCompatibleDC(HDC hdc)
	{
		return Handle<HDC>(::CreateCompatibleDC(hdc), true);
	}

	static auto GetDC(HWND hwnd)
	{
		return Handle<HDC>(::GetDC(hwnd), false);
	}

	static auto GetWindowDC(HWND hwnd)
	{
		return Handle<HDC>(::GetWindowDC(hwnd), false);
	}

	// static auto GetPaintDC(HWND hwnd)
	// {
		// return Handle<HDC>(GetDCEx(hwnd, nullptr, DCX_INTERSECTUPDATE|DCX_VALIDATE), false);
	// }

	~Handle()
	{
		if (handle)
		{
			if (owned)
				DeleteDC(handle);
#ifndef DEJAW_OWN_DC
			else
				ReleaseDC(WindowFromDC(handle), handle);
#endif
		}
	}

	operator HDC() const
	{
		return handle;
	}

private:

	Handle(HDC handle, bool owned) : handle(handle), owned(owned)
	{
	}
};
