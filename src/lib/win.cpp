#include "win.h"


void lib::win::init(WNDCLASSEX & wc, LPCSTR name, WNDPROC callback) noexcept
{
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	wc.hInstance = GetModuleHandle(nullptr);
	wc.hIcon = wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE+1);

	wc.lpszMenuName = nullptr;
	wc.lpszClassName = name;
	wc.lpfnWndProc = callback;
}

ATOM lib::win::install(WNDCLASSEX const & wc) noexcept
{
	return RegisterClassEx(&wc);
}

HWND lib::win::create(WNDCLASSEX const & wc, LPCSTR title) noexcept
{
	return CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT,
		wc.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
}

int lib::win::run(HWND hwnd, HACCEL haccel) noexcept
{
	MSG msg;

	while (true)
	{
		int const res = GetMessage(&msg, nullptr, 0, 0);

		if(0 == res) break; // WM_QUIT

		else if(res < 0)
		{
			// throw std::runtime_exception("error in main loop");
			return -1;
		}

		if(hwnd && haccel)
			TranslateAccelerator(hwnd, haccel, &msg);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void lib::win::closeWindow(HWND h) noexcept
{
	SendMessage(h, WM_CLOSE, 0, 0);
}

void lib::win::move(HWND hwnd, int x, int y) noexcept
{
	SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void lib::win::resize(HWND hwnd, int w, int h) noexcept
{
	SetWindowPos(hwnd, nullptr, 0, 0, w, h, SWP_NOZORDER | SWP_NOMOVE);
}

void lib::win::center(HWND hwnd) noexcept
{
	WindowRect c(hwnd);
	WindowRect p(GetParent(hwnd));

	auto const dx = (p.width() - c.width()) >> 1;
	auto const dy = (p.height() - c.height()) >> 1;

	move(hwnd, p.left + dx, p.top + dy);
}

COLORREF lib::win::setPenColor(HDC dc, COLORREF color) noexcept
{
	SelectObject(dc, GetStockObject(DC_PEN));
	return SetDCPenColor(dc, color);
}

COLORREF lib::win::setBrushColor(HDC dc, COLORREF color) noexcept
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	return SetDCBrushColor(dc, color);
}

lib::win::WindowRect::WindowRect(HWND hwnd) noexcept
{
	if (hwnd)
		GetWindowRect(hwnd, this);
	else
	{
		left = top = 0;
		right = GetSystemMetrics(SM_CXSCREEN);
		bottom = GetSystemMetrics(SM_CYSCREEN);
	}
}

lib::win::ClientRect::ClientRect(HWND hwnd) noexcept
{
	if (hwnd)
		GetClientRect(hwnd, this);
	else
	{
		left = top = 0;
		right = GetSystemMetrics(SM_CXSCREEN);
		bottom = GetSystemMetrics(SM_CYSCREEN);
	}
}
