#pragma once
#include <windows.h>

#include <bitset>
#include <map>


struct PianoGrid
{
	using Ticks = std::map<size_t, std::bitset<128>>;

	Ticks ticks;

	PianoGrid()
	{
		ticks[7][72] = 1;
		ticks[8][73] = 1;
		ticks[9][74] = 1;
	}

	void paint(HDC dc, RECT const & r, SIZE const & cellSize, int firstVisibleKey);
};
