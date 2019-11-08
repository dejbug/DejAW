#pragma once
#include <dejlib3/win.h>

struct grid_t
{
	RECT bounds;
	int cols, rows;
	int cw, ch, gap;

	grid_t() noexcept;

	void reset() noexcept;
	void setup(RECT const &, int cols, int rows, int gap=0);

	bool are_neighbors(int src, int dst) const noexcept;

	void paint(dejlib3::win::Dc & dc, RECT & r);
};
