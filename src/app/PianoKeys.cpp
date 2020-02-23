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


void PianoKeys::paint(HDC dc, RECT const & r, SIZE const & cellSize, int firstVisibleKey)
{
	int const textPaddingRight = 42;
	int const textPaddingTop = 8;

	int const right = r.right + 1;

	lib::win::selectStockObject(dc, DC_PEN);
	lib::win::selectStockObject(dc, DC_BRUSH);

	SelectObject(dc, GetStockObject(ANSI_FIXED_FONT));
	SetBkMode(dc, TRANSPARENT);

	COLORREF const backgroundColor1 = RGB(255, 255, 255);
	COLORREF const backgroundColor2 = RGB(128, 128, 128);
	COLORREF const textColor1 = RGB(0, 0, 0);
	COLORREF const textColor2 = RGB(255, 255, 255);
	COLORREF const borderColor = RGB(0, 0, 0);

	SetDCPenColor(dc, borderColor);
	SetDCBrushColor(dc, backgroundColor1);

	Rectangle(dc, r.left, r.top, right, r.bottom);

	for (int i=0, y=r.top; y<r.bottom; y += cellSize.cy, ++i)
	{
		MoveToEx(dc, r.left, y, NULL);
		LineTo(dc, right, y);

		int const reverseKeyIndex = 127 - (firstVisibleKey + i);
		auto const keyNamePair = getKeyName(reverseKeyIndex);

		if (keyNamePair.first[1] == '#')
		{
			SetTextColor(dc, textColor2);
			SetDCBrushColor(dc, backgroundColor2);

			lib::win::selectStockObject(dc, NULL_PEN);
			Rectangle(dc, r.left + 1, y + 1, right, y + cellSize.cy + 1);
			lib::win::selectStockObject(dc, DC_PEN);
		}
		else
		{
			SetTextColor(dc, textColor1);
			SetDCBrushColor(dc, backgroundColor1);
		}

		TextOut(dc, right - textPaddingRight, y + textPaddingTop, keyNamePair.first, keyNamePair.second);
	}
}
