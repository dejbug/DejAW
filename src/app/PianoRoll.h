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
		ticks[8][71] = 1;
	}

};


struct PianoRoll
{
	SIZE cellSize { 32, 32 };
	int firstVisibleKey = 71;
	int keyListWidth = 100;

	PianoGrid grid;

	void paint(HDC dc, RECT const & r);
};
