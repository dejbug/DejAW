#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <stdio.h>

#include <pool/dejlib2/error_t.h>
#include <pool/dejlib2/win.h>
#include <pool/dejlib3/win.h>

#include <main/resource.h>
#include <app/PianoRoll.h>

PianoRoll pianoRoll;

BOOL wm_create(HWND h, LPCREATESTRUCT cs)
{
	//~ DragAcceptFiles(h, TRUE);
	//~ pianoRoll.cellSize = { 16, 16 };
	return TRUE;
}

void wm_activate(HWND h, UINT f, HWND prev, BOOL minimized)
{
}

void wm_timer(HWND h, UINT id)
{
}

void wm_size(HWND h, UINT type, short cx, short cy)
{
}

void wm_paint(HWND h)
{
	COLORREF const b = RGB(0x3f,0x3f,0x3f);
	//~ COLORREF const f = RGB(0x83,0x8B,0x8B);
	//~ COLORREF const t = RGB(0x3f,0x3f,0xaf);

	RECT r;
	GetClientRect(h, &r);

	dejlib3::win::PaintDc dc(h, b, b);
	pianoRoll.paint(dc.handle, r);
}

void wm_keydown(HWND h, UINT key, BOOL, int repeatCount, UINT flags)
{
	switch(key)
	{
		case VK_F5:
			InvalidateRect(h, NULL, TRUE);
			UpdateWindow(h);
			break;
	}
}

void wm_command(HWND h, int id, HWND ctrl, UINT code)
{
	if(1 == code) /// -- handle accelerators.
		switch(id)
		{
			default: break;

			case IDM_ESCAPE:
				dejlib2::win::close_window(h);
				break;

			case IDM_F8:
				break;
		}
}

LRESULT CALLBACK MainFrameProc(HWND h, UINT m, WPARAM wParam, LPARAM lParam)
{
	try
	{
		switch(m)
		{
			default: break;

			// case WM_ERASEBKGND: return 0;
			HANDLE_MSG(h, WM_PAINT, wm_paint);
			HANDLE_MSG(h, WM_TIMER, wm_timer);
			HANDLE_MSG(h, WM_KEYDOWN, wm_keydown);
			HANDLE_MSG(h, WM_COMMAND, wm_command);
			HANDLE_MSG(h, WM_ACTIVATE, wm_activate);
			HANDLE_MSG(h, WM_SIZE, wm_size);
			HANDLE_MSG(h, WM_CREATE, wm_create);

			case WM_CLOSE: DestroyWindow(h); return 0;
			case WM_DESTROY: PostQuitMessage(0); return 0;

			case WM_APPCOMMAND:
			{
				auto const cmd = GET_APPCOMMAND_LPARAM(lParam);
				auto const dev = GET_DEVICE_LPARAM(lParam);
				auto const key = GET_KEYSTATE_LPARAM(lParam);
				printf("WM_APPCOMMAND cmd(%d) dev(%d) key(%d)\n", cmd, dev, key);
				return 0;
			}
		}
	}

	catch(dejlib2::error_t & e)
	{
		e.print();
	}

	return DefWindowProc(h, m, wParam, lParam);
}
