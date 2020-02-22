#include "PianoGrid.h"


void PianoGrid::paint(HDC dc, RECT const & r, int keyListWidth, SIZE const & cellSize, int firstVisibleKey)
{
	int const headerHeight = cellSize.cy;
	int const keysVisible = (r.bottom - (r.top + headerHeight)) / cellSize.cy + 1;

	for (auto [col, keys] : ticks)
	{
		for (int row = 0; row < keysVisible; ++row)
		{
			if (!keys[firstVisibleKey + row])
				continue;

			int const x = keyListWidth + col * cellSize.cx;
			int const y = headerHeight + row * cellSize.cy;
			int const p = 2;
			RECT const r2 = {x+p, y+p, x+cellSize.cx-p+1, y+cellSize.cy-p+1};
			auto const brush = reinterpret_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));

			FillRect(dc, &r2, brush);
		}
	}
}
