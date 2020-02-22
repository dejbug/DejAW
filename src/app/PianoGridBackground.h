#pragma once
#include <windows.h>


struct PianoGridBackground
{
	HDC mdc = nullptr;
	HBITMAP bmp = nullptr;
	SIZE size{};

	~PianoGridBackground();

	void cleanup();

	void create(HDC hdc, RECT const & r, SIZE const & cellSize);

	void paint(HDC hdc, RECT const & r);
};
