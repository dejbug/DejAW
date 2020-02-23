#pragma once
#include <windows.h>

#include "PianoKeys.h"
#include "PianoGrid.h"
#include "PianoGridBackground.h"


struct PianoRoll
{
	SIZE cellSize { 32, 32 };
	int firstVisibleKey = 71;
	int const headerHeight = 32;
	int const keyListWidth = 100;

	PianoKeys keys;
	PianoGrid grid;
	PianoGridBackground gridBackground;

	void resize(HDC dc, RECT const & r);
	void paint(HDC dc, RECT const & r);
};
