#include <windows.h>
#include <stdio.h>

#include <lib/win.h>


extern LRESULT CALLBACK MainFrameProc(HWND, UINT, WPARAM, LPARAM);


int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX wc;

	lib::win::init(wc, "DejAW:MAINFRAME", MainFrameProc);
	wc.hCursor = nullptr;

	lib::win::install(wc);

	HWND const hwnd = lib::win::create(wc, "DejAW");

	lib::win::resize(hwnd, 782, 400);
	lib::win::center(hwnd);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	HACCEL const haccel = LoadAccelerators(instance, "accel_main");

	return lib::win::run(hwnd, haccel);
}
