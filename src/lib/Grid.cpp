#include "Grid.h"

bool Grid::setCellSize(int w, int h)
{
	cellSize.cy = w > 0 ? w : 1;
	cellSize.cx = h > 0 ? h : 1;
	return cellSize.cx == w && cellSize.cy == h;
}

static void draw_line(HDC dc, POINT a, POINT b)
{
	MoveToEx(dc, a.x, a.y, NULL);
	LineTo(dc, b.x, b.y);
}

void Grid::paint(HDC dc, RECT const & r) const
{
	for (int x=r.left; x<r.right; x+=cellSize.cx)
		draw_line(dc, {x, r.top}, {x, r.bottom});

	for (int y=r.top; y<r.bottom; y+=cellSize.cy)
		draw_line(dc, {r.left, y}, {r.right, y});
}
