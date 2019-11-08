#pragma once
#include <windows.h>

namespace dejlib2 {

struct temp_hdc_t
{
	HWND parent;
	HDC handle;
	
	temp_hdc_t(HWND parent);
	virtual ~temp_hdc_t();
	
	temp_hdc_t(const temp_hdc_t&);
	temp_hdc_t& operator=(const temp_hdc_t&);
};

} // namespace dejlib2
