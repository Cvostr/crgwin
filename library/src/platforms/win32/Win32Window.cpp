#include "platforms/win32/Win32Window.hpp"
#include <platforms/win32/Win32Platform.hpp>
#include "platforms/win32/Win32Utils.hpp"
#ifdef _WIN32
#include <windows.h>
#endif

using namespace crgwin;

Win32Window::Win32Window(const WindowCreateInfo& create_info) : Window(create_info) {
	unsigned int win32_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        win32_ex_style = 0;

    LPCWSTR w_title = CStrToWSTR(_title.c_str());

    if (create_info.resize)
        win32_style |= WS_MAXIMIZEBOX | WS_THICKFRAME;

    int x = create_info.position.x;
    int y = create_info.position.y;

    if (x == WINDOW_DEFAULT_POS)
        x = CW_USEDEFAULT;
    if (y == WINDOW_DEFAULT_POS)
        y = CW_USEDEFAULT;

    win32_handle = CreateWindowExW(
        win32_ex_style,
        WIN32_WIN_CLASS_W,
        w_title,
        win32_style,
        x,
        y,
        _client_size.x,
        _client_size.y,
        nullptr,
        nullptr,
        Win32Platform::GetInstance(),
        nullptr);

    if (win32_handle == nullptr)
    {
        return;
    }

    Win32Platform::RegisterWindow(this);
}

Win32Window::~Win32Window() {
    Close();
}

HWND Win32Window::GetHWND() const {
    return win32_handle;
}

LRESULT Win32Window::WndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    }

    return DefWindowProcW(win32_handle, msg, wParam, lParam);
}

void Win32Window::SetTitle(const std::string& title) {
    PCWSTR w_title = CStrToWSTR(_title.c_str());
    if (::SetWindowTextW(win32_handle, w_title))
    {
        _title = title;
    }
}

void Win32Window::Show() {
    if (!_visible && win32_handle) {
        ::ShowWindow(win32_handle, SW_SHOW);
        _visible = true;
    }
}

void Win32Window::Hide() {
    if (_visible && win32_handle) {
        ::ShowWindow(win32_handle, SW_HIDE);
        _visible = false;
    }
}

void Win32Window::Minimize() {
    if(win32_handle)
        ::ShowWindow(win32_handle, SW_MINIMIZE);
}

void Win32Window::Maximize() {
    if (win32_handle)
        ::ShowWindow(win32_handle, SW_MAXIMIZE);
}

void Win32Window::Close() {
    if (win32_handle) {
        ::DestroyWindow(win32_handle);
        Win32Platform::UnregisterWindow(this);
        win32_handle = nullptr;
        _visible = false;
    }
}