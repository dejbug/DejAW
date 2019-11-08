#pragma once
#include <windows.h>

namespace dejlib2 {

struct mouse_info_t
{
	static bool has_mouse();
	static bool has_wheel();
	static bool buttons_swapped();
	static int get_buttons_count();
};

} // namespace dejlib2
