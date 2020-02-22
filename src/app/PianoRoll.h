#pragma once
#include <windows.h>

#include "PianoKeys.h"
#include "PianoGrid.h"


struct PianoRoll
{
	SIZE cellSize { 32, 32 };
	int firstVisibleKey = 71;
	int keyListWidth = 100;

	PianoKeys keys;
	PianoGrid grid;

	void paint(HDC dc, RECT const & r);
};
