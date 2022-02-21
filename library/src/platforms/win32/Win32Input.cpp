#include <platforms/win32/Win32Window.hpp>
#include <base/InputConstants.hpp>

#ifdef _WIN32
#include <windows.h>
#include <dwmapi.h>

KeyCode GetKeyCode(WPARAM win_code) {
    switch (win_code) {
    case VK_LCONTROL:
        return KEY_CODE_LCTRL;
    case VK_RCONTROL:
        return KEY_CODE_RCTRL;
    case VK_TAB:
        return KEY_CODE_TAB;
    case VK_LSHIFT:
        return KEY_CODE_LSHIFT;
    case VK_LMENU:
        return KEY_CODE_LALT;
    case VK_RMENU:
        return KEY_CODE_RALT;
    case VK_BACK:
        return KEY_CODE_BACKSPACE;
    case VK_SPACE:
        return KEY_CODE_SPACE;
    case VK_ESCAPE:
        return KEY_CODE_ESCAPE;
    case VK_RETURN:
        return KEY_CODE_ENTER;

    case VK_UP:
        return KEY_CODE_UP;
    case VK_DOWN:
        return KEY_CODE_DOWN;
    case VK_LEFT:
        return KEY_CODE_LEFT;
    case VK_RIGHT:
        return KEY_CODE_RIGHT;
    case VK_DELETE:
        return KEY_CODE_DELETE;

    case VK_F1:
        return KEY_CODE_F1;
    case VK_F2:
        return KEY_CODE_F2;
    case VK_F3:
        return KEY_CODE_F3;
    case VK_F4:
        return KEY_CODE_F4;
    case VK_F5:
        return KEY_CODE_F5;
    case VK_F6:
        return KEY_CODE_F6;
    case VK_F7:
        return KEY_CODE_F7;
    case VK_F8:
        return KEY_CODE_F8;
    case VK_F9:
        return KEY_CODE_F9;
    case VK_F10:
        return KEY_CODE_F10;
    case VK_F11:
        return KEY_CODE_F11;
    case VK_F12:
        return KEY_CODE_F12;

    case 0x41:
        return KEY_CODE_A;
    case 0x42:
        return KEY_CODE_B;
    case 0x43:
        return KEY_CODE_C;
    case 0x44:
        return KEY_CODE_D;
    case 0x45:
        return KEY_CODE_E;
    case 0x46:
        return KEY_CODE_F;
    case 0x47:
        return KEY_CODE_G;
    case 0x48:
        return KEY_CODE_H;
    case 0x49:
        return KEY_CODE_I;
    case 0x4A:
        return KEY_CODE_J;
    case 0x4B:
        return KEY_CODE_K;
    case 0x4C:
        return KEY_CODE_L;
    case 0x4D:
        return KEY_CODE_M;
    case 0x4E:
        return KEY_CODE_N;
    case 0x4F:
        return KEY_CODE_O;
    case 0x50:
        return KEY_CODE_P;
    case 0x51:
        return KEY_CODE_Q;
    case 0x52:
        return KEY_CODE_R;
    case 0x53:
        return KEY_CODE_S;
    case 0x54:
        return KEY_CODE_T;
    case 0x55:
        return KEY_CODE_U;
    case 0x56:
        return KEY_CODE_V;
    case 0x57:
        return KEY_CODE_W;
    case 0x58:
        return KEY_CODE_X;
    case 0x59:
        return KEY_CODE_Y;
    case 0x5A:
        return KEY_CODE_Z;
    }
    return (KeyCode)0;
}

void crgwin::Win32Window::WndProcInput(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
        keydown(GetKeyCode(wParam));
        break;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
        keyup(GetKeyCode(wParam));
        break;
    }
	}
}

#endif