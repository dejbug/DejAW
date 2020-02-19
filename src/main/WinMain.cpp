#include <windows.h>

#include <pool/dejlib3/win.h>
#include <pool/dejlib2/window_class_t.h>
#include <pool/dejlib2/window_maker_t.h>
#include <pool/dejlib2/window_positioner_t.h>

extern LRESULT CALLBACK MainFrameProc(HWND, UINT, WPARAM, LPARAM);

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	try
	{
		HACCEL haccel = LoadAccelerators(instance, "accel_main");

		dejlib2::window_class_t wc("DejAW:MAINFRAME", MainFrameProc);
		wc.hCursor = nullptr;

		dejlib2::window_maker_t wm(wc);

		wc.install();
		wm.create();

		dejlib2::window_positioner_t wp(wm.handle);
		wp.setsize(782, 400);
		wp.center_to_screen();

		SetWindowText(wm.handle, "DejAW");
		UpdateWindow(wm.handle);
		ShowWindow(wm.handle, SW_SHOW);

		return dejlib3::win::run(wm.handle, haccel);
	}

	catch(dejlib2::error_t& e)
	{
		e.print();
	}

	return -1;
}
