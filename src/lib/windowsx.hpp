#pragma once

#define HANDLE_WM_APPCOMMAND(hwnd,wParam,lParam,fn) ((fn)((hwnd),GET_APPCOMMAND_LPARAM(lParam),GET_MOUSEORKEY_LPARAM(lParam),GET_KEYSTATE_LPARAM(lParam)),(LRESULT)0)

#define HANDLE_WM_CAPTURECHANGED(hwnd,wParam,lParam,fn) ((fn)((hwnd),(HWND)(lParam)),(LRESULT)0)
