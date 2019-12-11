#include "PianoRoll.h"
#include <cassert>
#include <utility> // std::pair
#include <lib/win.h>
#include <lib/Grid.h>
#include <pool/dejlib3/win.h>

void PianoRoll::paint(HDC dc, RECT const & r)
{
	paintChannelList(dc, r);
	paintNoteList(dc, r);
	paintGrid(dc, r);
}

void PianoRoll::paintChannelList(HDC dc, RECT const & r)
{
	lib::win::setPenColor(dc, RGB(0, 0, 0));
	lib::win::setBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, r.left, r.top, r.left + 200 + 1, r.bottom);
}

static std::pair<char, bool> getKeyChar(int i)
{
	if (i < 0 || i > 127) return std::make_pair(0, false);

	constexpr char const keyChars[] {'A', 0, 'B', 'C', 0, 'D', 0, 'E', 'F', 0, 'G', 0};

	/// Key char with no sharp.
	if (keyChars[i] != 0)
		return std::make_pair(keyChars[i], false);

	/// We assume that i==0 will never happen at this point.
	/// If it does it means that the scale starts with a sharp,
	/// which means that i-1 will not point to a valid char.
	assert(i >= 1 && "this algorithm is optimized for the major scale");

	/// We will have to do this differently for scales
	/// which start with a sharp; doing something like
	/// std::make_pair(keyChars[i+1]-1, true).

	/// Key char with sharp.
	return std::make_pair(keyChars[i-1], true);
}

static std::pair<char const *, size_t> getKeyName(int i)
{
	if (i < 0 || i > 127) return std::make_pair("", 0);

	static char keyBuffer[8] { "" };

	int const octaveIndex = i / 12;
	auto const keyCharPair = getKeyChar(i % 12);

	int keyBufferIndex = 0;

	keyBuffer[keyBufferIndex++] = keyCharPair.first;

	if (keyCharPair.second)
		keyBuffer[keyBufferIndex++] = '#';

	if (octaveIndex < 10)
	{
		keyBuffer[keyBufferIndex++] = '0' + octaveIndex;
	}
	else
	{
		keyBuffer[keyBufferIndex++] = '0' + (octaveIndex / 10);
		keyBuffer[keyBufferIndex++] = '0' + (octaveIndex % 10);
	}

	keyBuffer[keyBufferIndex] = 0;

	return std::make_pair(keyBuffer, keyBufferIndex);
}

void PianoRoll::paintNoteList(HDC dc, RECT const & r)
{
	// using PianoRoll::cellSize.cy;

	int const left = r.left + 200;
	int const right = left + 100 + 1;

	lib::win::setPenColor(dc, RGB(0, 0, 0));
	lib::win::setBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, left, r.top, right, r.bottom);

	int const keyOffset = 70;

	lib::win::setBrushColor(dc, RGB(128, 128, 128));
	SetBkMode(dc, TRANSPARENT);
	SelectObject(dc, GetStockObject(ANSI_FIXED_FONT));

	for (int i=0, y=r.top; y<r.bottom; y += cellSize.cy, ++i)
	{
		MoveToEx(dc, left, y, NULL);
		LineTo(dc, right, y);

		if (i == 0) continue;

		int const reverseKeyIndex = 127 - (keyOffset + i);
		auto keyNamePair = getKeyName(reverseKeyIndex);

		if (keyNamePair.first[1] == '#')
		{
			SetTextColor(dc, RGB(255,255,255));

			SelectObject(dc, GetStockObject(NULL_PEN));
			Rectangle(dc, left + 1, y + 1, right, y + cellSize.cy + 1);
			lib::win::setPenColor(dc, RGB(0, 0, 0));
		}
		else
		{
			SetDCPenColor(dc, RGB(0, 0, 0));
			SetTextColor(dc, RGB(0,0,0));
		}

		TextOut(dc, right - 28, y + 8, keyNamePair.first, keyNamePair.second);
	}
}

void PianoRoll::paintGrid(HDC dc, RECT const & r)
{
	Grid grid;
	grid.setCellSize(cellSize.cx, cellSize.cy);

	RECT r2 { r.left + 300, r.top + 32, r.right, r.bottom };
	grid.paint(dc, r2);
}
