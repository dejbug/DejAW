#include "PianoGridBackground.h"


PianoGridBackground::~PianoGridBackground()
{
	cleanup();
}

static void draw_line(HDC dc, POINT a, POINT b)
{
	MoveToEx(dc, a.x, a.y, NULL);
	LineTo(dc, b.x, b.y);
}

void PianoGridBackground::cleanup()
{
	if (mdc) {
		SelectObject(mdc, (HBITMAP)nullptr);
		DeleteDC(mdc);
	}
	if (bmp)
		DeleteObject(bmp);
}

void PianoGridBackground::create(HDC hdc, RECT const & r, SIZE const & cellSize)
{
	cleanup();

	size = {r.right - r.left, r.bottom - r.top};

	mdc = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc, size.cx, size.cy);
	SelectObject(mdc, bmp);

	BitBlt(mdc, 0, 0, size.cx, size.cy, nullptr, 0, 0, WHITENESS);

	for (int x=0; x<size.cx; x+=cellSize.cx)
		draw_line(mdc, {x, 0}, {x, size.cy});

	for (int y=0; y<size.cy; y+=cellSize.cy)
		draw_line(mdc, {0, y}, {size.cx, y});
}

void PianoGridBackground::paint(HDC hdc, RECT const & r)
{
	BitBlt(hdc, r.left, r.top, size.cx, size.cy, mdc, 0, 0, SRCCOPY);
}
