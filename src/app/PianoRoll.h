#pragma once
#include <windows.h>

struct PianoRoll
{
	SIZE cellSize { 32, 32 };
	int firstVisibleKey = 71;
	int keyListWidth = 100;

	void paint(HDC dc, RECT const & r);
};
