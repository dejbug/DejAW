#pragma once
#include <windows.h>
#include "error_t.h"

namespace dejlib2 {

struct dll_t
{
	HINSTANCE handle;
	bool autofree;

	dll_t(char const * fpath, bool autofree=false);
	virtual ~dll_t();

	void free();
};

} // namespace dejlib2
