#pragma once
#include <windows.h>


struct PianoKeys
{
	void paint(HDC dc, RECT const & r, int keyListWidth, SIZE const & cellSize, int firstVisibleKey);
};
