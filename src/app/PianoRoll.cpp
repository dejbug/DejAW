#include "PianoRoll.h"


void PianoRoll::paint(HDC dc, RECT const & r)
{
	keys.paint(dc, r, keyListWidth, cellSize, firstVisibleKey);
	grid.paint(dc, r, keyListWidth, cellSize, firstVisibleKey);
}
