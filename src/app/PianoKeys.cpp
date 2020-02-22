#include "PianoRoll.h"

#include <cassert>
#include <utility> // std::pair

#include <lib/win.h>


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


void PianoKeys::paint(HDC dc, RECT const & r, int keyListWidth, SIZE const & cellSize, int firstVisibleKey)
{
	int const headerHeight = cellSize.cy;
	int const textPaddingRight = 42;
	int const textPaddingTop = 8;

	int const left = r.left;
	int const right = left + keyListWidth + 1;

	lib::win::setPenColor(dc, RGB(0, 0, 0));
	lib::win::setBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, left, r.top + headerHeight, right, r.bottom);

	lib::win::setBrushColor(dc, RGB(128, 128, 128));
	SetBkMode(dc, TRANSPARENT);
	SelectObject(dc, GetStockObject(ANSI_FIXED_FONT));

	for (int i=0, y=r.top + headerHeight; y<r.bottom; y += cellSize.cy, ++i)
	{
		MoveToEx(dc, left, y, NULL);
		LineTo(dc, right, y);

		int const reverseKeyIndex = 127 - (firstVisibleKey + i);
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

		TextOut(dc, right - textPaddingRight, y + textPaddingTop, keyNamePair.first, keyNamePair.second);
	}
}
