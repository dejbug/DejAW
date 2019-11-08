#include "grid_t.h"
#include <dejlib2/error_t.h>
#include <dejlib2/errors.h>

void grid_t::setCellSize(int w, int h)
{
	if(w <= 0 || h <= 0)
		throw dejlib2::error_t(dejlib2::err::ARGS);

	cw = w;
	ch = h;
}

void grid_t::paint(dejlib3::win::Dc & dc, RECT & r)
{
	for (int x=r.left; x<r.right; x+=cw)
		draw_line(dc, {x, r.top}, {x, r.bottom});

	for (int y=r.top; y<r.bottom; y+=ch)
		draw_line(dc, {r.left, y}, {r.right, y});
}
