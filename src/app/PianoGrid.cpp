#include "PianoGrid.h"


void PianoGrid::paint(HDC dc, RECT const & r, SIZE const & cellSize, int firstVisibleKey)
{
	int const keysVisible = (r.bottom - r.top) / cellSize.cy + 1;

	auto const brush = reinterpret_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));

	for (auto const & [col, keys] : ticks)
	{
		for (int row = 0; row < keysVisible; ++row)
		{
			if (!keys[firstVisibleKey + row])
				continue;

			int const x = r.left + col * cellSize.cx;
			int const y = r.top + row * cellSize.cy;
			int const p = 2;

			RECT const r2 = {x+p, y+p, x+cellSize.cx-p+1, y+cellSize.cy-p+1};

			FillRect(dc, &r2, brush);
		}
	}
}
