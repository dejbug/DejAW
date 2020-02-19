#pragma once
#include <windows.h>

struct PianoRoll
{
	SIZE cellSize { 32, 32 };
	int keyOffset = 70;

	void paint(HDC dc, RECT const & r);

	void paintChannelList(HDC dc, RECT const & r);
	void paintNoteList(HDC dc, RECT const & r);
	void paintGrid(HDC dc, RECT const & r);
};
