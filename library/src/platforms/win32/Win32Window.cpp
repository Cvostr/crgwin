#include "platforms/win32/Win32Window.hpp"
#include <platforms/win32/Win32Platform.hpp>
#include "platforms/win32/Win32Utils.hpp"
#ifdef _WIN32
#include <windows.h>
#include <dwmapi.h>

using namespace crgwin;

Win32Window::Win32Window(const WindowCreateInfo& create_info) : Window(create_info) {
    unsigned int win32_style = WS_POPUP,
        win32_ex_style = 0;

    if (!create_info.borderless) {
        //window isn't borderless
        win32_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    }
    else {
        //window borderless
        win32_style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        win32_ex_style |= WS_EX_WINDOWEDGE;
    }
    //Convert UTF-8 title to unicode
    LPCWSTR w_title = CStrToWSTR(_title.c_str());
    
    if (create_info.resize)
        //if window should be resizeable, add maximize button in titlebar and resizeable corners
        win32_style |= WS_MAXIMIZEBOX | WS_SIZEBOX;

    int x = create_info.position.x;
    int y = create_info.position.y;
    int width = _client_size.x;
    int height = _client_size.y;

    if (x == WINDOW_DEFAULT_POS)
        x = CW_USEDEFAULT;
    if (y == WINDOW_DEFAULT_POS)
        y = CW_USEDEFAULT;

    RECT winRect = { 0, 0, width, height };
    if (!create_info.borderless) {
        AdjustWindowRectEx(&winRect, win32_style, FALSE, win32_ex_style);
        width = winRect.right - winRect.left;
        height = winRect.bottom - winRect.top;
    }
    //create window
    win32_handle = ::CreateWindowExW(
        win32_ex_style,
        WIN32_WIN_CLASS_W,
        w_title,
        win32_style,
        x,
        y,
        width,
        height,
        nullptr,
        nullptr,
        Win32Platform::GetInstance(),
        nullptr);

    if (win32_handle == nullptr)
    {
        //error creating window
        return;
    }

    if (!create_info.borderless) {
        crgwin::ivec2 pos = this->GetWindowPos();
        pos.x += winRect.left;
        pos.y += winRect.top;
        this->SetWindowPos(pos);
    }

    //register window in list
    Win32Platform::RegisterWindow(this);
}

Win32Window::~Win32Window() {
    Close();
}

WindowHandle Win32Window::GetNativeHandle() const {
    return win32_handle;
}

LRESULT Win32Window::WndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
    if (WndProcInput(msg, wParam, lParam))
        return true;
    WindowEvent r_event;
    switch (msg)
    {
    case WM_SIZE:
    {
        if (wParam == SIZE_MINIMIZED){
           //on window minimized
            _state = WindowState::STATE_MINIMIZED;
            r_event.type = WindowEventType::EVENT_STATE_CHANGED;
            r_event.state = WindowState::STATE_MINIMIZED;
            CallEvent(r_event);
        }
        else if(wParam == SIZE_MAXIMIZED){
           //on window maximized
            _state = WindowState::STATE_MAXIMIZED;
            r_event.type = WindowEventType::EVENT_STATE_CHANGED;
            r_event.state = WindowState::STATE_MAXIMIZED;
            CallEvent(r_event);
        }
        else if (wParam == SIZE_RESTORED) {
            _state = WindowState::STATE_DEFAULT;
            //on size restored
            if (_resizing) {
                //window resized by user
                r_event.type = WindowEventType::EVENT_SIZE_CHANGED;
                CallEvent(r_event);
            }
            else {
                //window resized by API
            }
        }
        break;
    }
    case WM_SETFOCUS:
        //On got focus function
        _focused = true;
        break;
    case WM_KILLFOCUS:
        //on lost focus function
        _focused = false;
        break;
    case WM_CLOSE:
        //on window closed by user
        Close();
        return 0;
    case WM_ENTERSIZEMOVE:
        //on user resizing window
        _resizing = true;
        break;
    case WM_EXITSIZEMOVE:
        //on user end resizing window
        _resizing = false;
        break;
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

crgwin::ivec2 Win32Window::GetWindowPos() {
    if (!win32_handle)
        return crgwin::ivec2(-1, -1);

    RECT rect;
    GetWindowRect(win32_handle, &rect);
    return crgwin::ivec2(rect.left, rect.top);
}

void Win32Window::SetWindowPos(crgwin::ivec2 pos) {
    if (win32_handle) {
        ::SetWindowPos(win32_handle,
            nullptr, pos.x, pos.y, 0, 0,
            SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    }
}

void Win32Window::Resize(const crgwin::ivec2& size) {
    if (win32_handle) {
        int width = size.x;
        int height = size.y;

        if (!_create_info.borderless) {
            WINDOWINFO winInfo;
            memset(&winInfo, 0, sizeof(WINDOWINFO));
            winInfo.cbSize = sizeof(winInfo);
            GetWindowInfo(win32_handle, &winInfo);

            RECT winRect = { 0, 0, size.x, size.y };
            AdjustWindowRectEx(&winRect, winInfo.dwStyle, FALSE, winInfo.dwExStyle);
            width = winRect.right - winRect.left;
            height = winRect.bottom - winRect.top;
        }

        ivec2 pos = this->GetWindowPos();

        ::SetWindowPos(win32_handle, nullptr, pos.x, pos.y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
        _client_size = size;
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

void Win32Window::Restore() {
    if (win32_handle) {
        ::ShowWindow(win32_handle, SW_RESTORE);
    }
}

#endif