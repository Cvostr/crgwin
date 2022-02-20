#include <platforms/win32/Win32Platform.hpp>
#include <platforms/win32/Win32Window.hpp>

#ifdef _WIN32
#include <windows.h>
#include "string.h"
#include <algorithm>

std::vector<crgwin::Win32Window*> crgwin::Win32Platform::windows;

HINSTANCE crgwin::Win32Platform::GetInstance() {
    return GetModuleHandle(NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void crgwin::Win32Platform::RegisterWindowClass() {
    WNDCLASSW windowsClass;
    memset(&windowsClass, 0, sizeof(WNDCLASS));
    windowsClass.style = CS_DBLCLKS;
    windowsClass.lpfnWndProc = WndProc; 
    windowsClass.hInstance = GetInstance();
    windowsClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowsClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowsClass.lpszClassName = WIN32_WIN_CLASS_W;
    windowsClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //+1 to differentiate between background and scrollbar

    if (!RegisterClassW((const WNDCLASSW*)&windowsClass))
    {
        //error registering window class
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Find window to process that message
    if (hwnd != nullptr)
    {
        // Find window by handle
        const auto win = crgwin::Win32Platform::GetByHWND(hwnd);
        if (win)
        {
            return (win)->WndProc(msg, wParam, lParam);
        }
    }

    // Default
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void crgwin::Win32Platform::Tick() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        // Translate the message and dispatch it to WindowProc()
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void crgwin::Win32Platform::RegisterWindow(Win32Window* window) {
    if (GetByHWND(window->GetHWND()))
        return;
    
    windows.push_back(window);
}
void crgwin::Win32Platform::UnregisterWindow(Win32Window* window) {
    if (GetByHWND(window->GetHWND())) {
        std::remove(windows.begin(), windows.end(), window);
        windows.pop_back();
    }
}
crgwin::Win32Window* crgwin::Win32Platform::GetByHWND(HWND hwnd) {
    for (auto& win : windows) {
        if (win->GetHWND() == hwnd)
            return win;
    }
    return nullptr;
}

#endif