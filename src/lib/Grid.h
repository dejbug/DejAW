#pragma once
#include <windows.h>

struct Grid
{
	SIZE cellSize { 1, 1 };

	bool setCellSize(int w, int h);

	void paint(HDC dc, RECT const & r) const;
};
