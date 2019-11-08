#include "grid_t.h"
#include <dejlib2/error_t.h>
#include <dejlib2/errors.h>


grid_t::grid_t() noexcept
{
	reset();
}

void grid_t::reset() noexcept
{
	SetRect(&bounds, 0, 0, 0, 0);
	cols = rows = gap = 0;
	cw = ch = 0;
}

void grid_t::setup(RECT const & r, int cols, int rows, int gap)
{
	reset();

	int const rw = r.right - r.left;
	int const rh = r.bottom - r.top;

	if(cols <= 0 || rows <= 0)
		throw dejlib2::error_t(dejlib2::err::ARGS);

	cw = rw / cols;
	ch = rh / rows;

	if(cw <= 0 || ch <= 0)
		throw dejlib2::error_t(dejlib2::err::ARGS);

	CopyRect(&bounds, &r);
	this->cols = cols;
	this->rows = rows;
	this->gap = gap;
}

bool grid_t::are_neighbors(int src, int dst) const noexcept
{
	return (
		src + 1 == dst ||
		src - 1 == dst ||
		src + cols == dst ||
		src - cols == dst
	);
}

void grid_t::paint(dejlib3::win::Dc & dc, RECT & r)
{
	for (int i=0, x=bounds.left; i<cols+1; ++i, x+=cw)
		draw_line(dc, {x, bounds.top}, {x, bounds.bottom});

	for (int i=0, y=bounds.top; i<rows+1; ++i, y+=ch)
		draw_line(dc, {bounds.left, y}, {bounds.right, y});
}
