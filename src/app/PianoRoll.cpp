#include "PianoRoll.h"


void PianoRoll::resize(HDC dc, RECT const & r)
{
	gridBackground.create(dc, r, cellSize);
}


void PianoRoll::paint(HDC dc, RECT const & r)
{
	RECT const rk = {
		r.left,
		r.top + headerHeight,
		r.left + keyListWidth,
		r.bottom };

	RECT const rg = {
		r.left + keyListWidth,
		r.top + headerHeight,
		r.right,
		r.bottom };

	gridBackground.paint(dc, rg);

	keys.paint(dc, rk, cellSize, firstVisibleKey);
	grid.paint(dc, rg, cellSize, firstVisibleKey);
}
