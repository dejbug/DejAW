#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>

#include <stdio.h>

#include <stdexcept>

#include <lib/win.h>
#include <lib/Handle.hpp>
#include <lib/windowsx.hpp>

#include <app/PianoRoll.h>

#include <main/resource.h>


static PianoRoll pianoRoll;
static bool dragging = false;


static BOOL wm_create(HWND h, LPCREATESTRUCT cs)
{
	// DragAcceptFiles(h, TRUE);
	// pianoRoll.cellSize = { 16, 16 };
	return TRUE;
}


static void wm_activate(HWND h, UINT f, HWND prev, BOOL minimized)
{
}


static void wm_timer(HWND h, UINT id)
{
}


static void wm_size(HWND h, UINT type, short cx, short cy)
{
	pianoRoll.resize(Handle<HDC>::GetDC(h), {0, 0, cx, cy});
}


static void wm_paint(HWND h)
{
	RECT r;
	GetClientRect(h, &r);

	PAINTSTRUCT ps;
	BeginPaint(h, &ps);

	lib::win::whiteness(ps.hdc, r.left, r.top, r.right, pianoRoll.headerHeight);
	pianoRoll.paint(ps.hdc, r);

	EndPaint(h, &ps);
}


static void wm_keydown(HWND h, UINT key, BOOL, int repeatCount, UINT flags)
{
	switch(key)
	{
		case VK_F5:
			InvalidateRect(h, NULL, TRUE);
			UpdateWindow(h);
			break;
	}
}


static void handle_accelerators(HWND h, int id)
{
	switch(id)
	{
		default: break;

		case IDM_ESCAPE:
			lib::win::closeWindow(h);
			break;

		case IDM_F8:
			break;
	}
}


static void wm_command(HWND h, int id, HWND ctrl, UINT code)
{
	if(1 == code)
		handle_accelerators(h, id);
}


static void wm_mousewheel(HWND h, int x, int y, int zDelta, UINT fwKeys)
{
	pianoRoll.firstVisibleKey += zDelta > 0 ? -1 : 1;
	InvalidateRect(h, nullptr, TRUE);
}


static void wm_mousemove(HWND h, int x, int y, UINT keyFlags)
{
	SetCursor(LoadCursor(nullptr, dragging ? IDC_HAND : IDC_ARROW));
}


static void wm_lbuttondown(HWND h, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
}


static void wm_lbuttonup(HWND h, int x, int y, UINT keyFlags)
{
}


static void wm_rbuttondown(HWND h, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	SetCapture(h);
	dragging = true;
	SetCursor(LoadCursor(nullptr, dragging ? IDC_HAND : IDC_ARROW));
}


static void wm_rbuttonup(HWND h, int x, int y, UINT keyFlags)
{
	ReleaseCapture();
	dragging = false;
	SetCursor(LoadCursor(nullptr, dragging ? IDC_HAND : IDC_ARROW));
}


static void wm_capturechanged(HWND h, HWND hwndNewCapture)
{
	dragging = false;
}


static void wm_appcommand(HWND h, short cmd, WORD dev, WORD key)
{
	printf("WM_APPCOMMAND cmd(%d) dev(%d) key(%d)\n", cmd, dev, key);
}


LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM wParam, LPARAM lParam)
{
	try
	{
		switch(m)
		{
			default: break;

			case WM_ERASEBKGND: return 0;

			HANDLE_MSG(h, WM_PAINT, wm_paint);
			HANDLE_MSG(h, WM_TIMER, wm_timer);
			HANDLE_MSG(h, WM_KEYDOWN, wm_keydown);
			HANDLE_MSG(h, WM_COMMAND, wm_command);

			HANDLE_MSG(h, WM_MOUSEWHEEL, wm_mousewheel);
			HANDLE_MSG(h, WM_MOUSEMOVE, wm_mousemove);
			HANDLE_MSG(h, WM_LBUTTONDOWN, wm_lbuttondown);
			HANDLE_MSG(h, WM_LBUTTONUP, wm_lbuttonup);
			HANDLE_MSG(h, WM_RBUTTONDOWN, wm_rbuttondown);
			HANDLE_MSG(h, WM_RBUTTONUP, wm_rbuttonup);
			HANDLE_MSG(h, WM_CAPTURECHANGED, wm_capturechanged);
			HANDLE_MSG(h, WM_APPCOMMAND, wm_appcommand);

			HANDLE_MSG(h, WM_SIZE, wm_size);
			HANDLE_MSG(h, WM_ACTIVATE, wm_activate);
			HANDLE_MSG(h, WM_CREATE, wm_create);

			case WM_CLOSE: DestroyWindow(h); return 0;
			case WM_DESTROY: PostQuitMessage(0); return 0;
		}
	}

	catch(std::runtime_error & e)
	{
		fprintf(stderr, "! %s\n", e.what());
	}

	return DefWindowProc(h, m, wParam, lParam);
}
