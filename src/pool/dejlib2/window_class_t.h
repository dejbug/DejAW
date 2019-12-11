#pragma once
#include <windows.h>

#include "errors.h"
#include "error_t.h"

namespace dejlib2 {

struct window_class_t : public WNDCLASSEX
{
	window_class_t(LPCSTR name, WNDPROC callback=DefWindowProc);
	
	void zeromemory();
	void init();
	void install();
	void uninstall();
	void load();
};

} // namespace dejlib2
