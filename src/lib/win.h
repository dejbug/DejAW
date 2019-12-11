#pragma once
#include <windows.h>

namespace lib {
namespace win {

COLORREF setPenColor(HDC dc, COLORREF color);
COLORREF setBrushColor(HDC dc, COLORREF color);

} // !namespace win
} // !namespace lib
