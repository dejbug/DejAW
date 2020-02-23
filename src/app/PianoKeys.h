#pragma once
#include <windows.h>


struct PianoKeys
{
	void paint(HDC dc, RECT const & r, SIZE const & cellSize, int firstVisibleKey);
};
