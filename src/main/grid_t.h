#pragma once
#include <dejlib3/win.h>

struct grid_t
{
	int cw{0}, ch{0};

	void setCellSize(int w, int h);

	void paint(dejlib3::win::Dc & dc, RECT & r);
};
