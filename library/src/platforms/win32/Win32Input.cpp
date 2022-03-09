#include <platforms/win32/Win32Window.hpp>
#include <base/InputConstants.hpp>

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#include "platforms/PlatformKeyMap.hpp"

static crgwin::PlatformKeyMappings win32_mappings;

crgKeyCode GetKeyCode(WPARAM win_code) {
    return win32_mappings.GetKeyMapping(win_code);
}

void crgwin::InitKeyCodes() {
    crgwin::KeyMappingPair mappings[] = 
    { {0x41, KEY_CODE_A}, {0x42, KEY_CODE_B}, {0x43, KEY_CODE_C},
      {0x44, KEY_CODE_D}, {0x45, KEY_CODE_E}, {0x46, KEY_CODE_F},
      {0x47, KEY_CODE_G}, {0x48, KEY_CODE_H}, {0x49, KEY_CODE_I},
      {0x4A, KEY_CODE_J}, {0x4B, KEY_CODE_K}, {0x4C, KEY_CODE_L}, 
      {0x4D, KEY_CODE_M}, {0x4E, KEY_CODE_N}, {0x4F, KEY_CODE_O},
      {0x50, KEY_CODE_P}, {0x51, KEY_CODE_Q}, {0x52, KEY_CODE_R},
      {0x53, KEY_CODE_S}, {0x54, KEY_CODE_T}, {0x55, KEY_CODE_U},
      {0x56, KEY_CODE_V}, {0x57, KEY_CODE_W}, {0x58, KEY_CODE_X}, 
      {0x59, KEY_CODE_Y}, {0x5A, KEY_CODE_Z},
      {VK_F1, KEY_CODE_F1}, {VK_F2, KEY_CODE_F2}, {VK_F3, KEY_CODE_F3},
      {VK_F4, KEY_CODE_F4}, {VK_F5, KEY_CODE_F5}, {VK_F6, KEY_CODE_F6},
      {VK_F7, KEY_CODE_F7}, {VK_F8, KEY_CODE_F8}, {VK_F9, KEY_CODE_F9},
      {VK_F10, KEY_CODE_F10}, {VK_F11, KEY_CODE_F11}, {VK_F12, KEY_CODE_F12},
      {VK_UP, KEY_CODE_UP}, {VK_DOWN, KEY_CODE_DOWN}, {VK_LEFT, KEY_CODE_LEFT}, {VK_RIGHT, KEY_CODE_RIGHT},
       
      {0x30, KEY_CODE_0}, {0x31, KEY_CODE_1}, {0x32, KEY_CODE_2},
      {0x33, KEY_CODE_3}, {0x34, KEY_CODE_4}, {0x35, KEY_CODE_5},
      {0x36, KEY_CODE_6}, {0x37, KEY_CODE_7}, {0x38, KEY_CODE_8}, {0x39, KEY_CODE_9},

      {VK_DELETE, KEY_CODE_DELETE}, {VK_NEXT, KEY_CODE_PAGEDOWN}, {VK_PRIOR, KEY_CODE_PAGEUP},
      {VK_INSERT, KEY_CODE_INSERT}, {VK_HOME, KEY_CODE_HOME}, {VK_END, KEY_CODE_END},
      {VK_RETURN, KEY_CODE_ENTER}, {VK_CAPITAL, KEY_CODE_CAPS_LOCK}, {VK_ESCAPE, KEY_CODE_ESCAPE},
      {VK_SPACE, KEY_CODE_SPACE}, {VK_BACK, KEY_CODE_BACKSPACE}, {VK_TAB, KEY_CODE_TAB},

      {VK_CONTROL, KEY_CODE_LCTRL}, {VK_LCONTROL, KEY_CODE_LCTRL}, {VK_RCONTROL, KEY_CODE_RCTRL},
      {VK_SHIFT, KEY_CODE_LSHIFT}, {VK_LSHIFT, KEY_CODE_LSHIFT}, {VK_RSHIFT, KEY_CODE_RSHIFT},
      {VK_MENU, KEY_CODE_LALT}, {VK_LMENU, KEY_CODE_LALT}, {VK_RMENU, KEY_CODE_RALT}
    };

    win32_mappings.AddKeyMappings(mappings, sizeof(mappings) / sizeof(crgwin::KeyMappingPair));

}

bool crgwin::Win32Window::WndProcInput(UINT msg, WPARAM wParam, LPARAM lParam) {
    bool result = false;
    WindowEvent r_event;

	switch (msg) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
        r_event.type = WindowEventType::EVENT_KEYDOWN;
        r_event.key = GetKeyCode(wParam);
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
        r_event.type = WindowEventType::EVENT_KEYUP;
        r_event.key = GetKeyCode(wParam);
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_MOUSEMOVE:
    {
        POINT p;
        p.x = static_cast<LONG>(GET_X_LPARAM(lParam));
        p.y = static_cast<LONG>(GET_Y_LPARAM(lParam));
        //::ClientToScreen(win32_handle, &p);
        r_event.type = WindowEventType::EVENT_MOUSE_MOVED;
        r_event.coord = crgwin::ivec2(p.x, p.y);
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_LBUTTONDOWN:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_DOWN;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_LEFT;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_RBUTTONDOWN:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_DOWN;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_RIGHT;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_MBUTTONDOWN:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_DOWN;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_MIDDLE;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_LBUTTONUP:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_UP;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_LEFT;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_RBUTTONUP:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_UP;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_RIGHT;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_MBUTTONUP:
    {
        r_event.type = WindowEventType::EVENT_MOUSE_BTN_UP;
        r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_MIDDLE;
        CallEvent(r_event);
        result = true;
        break;
    }
    case WM_MOUSEWHEEL: 
    {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
        int xpos = LOWORD(lParam);
        int ypos = LOWORD(lParam);

        r_event.type = WindowEventType::EVENT_MOUSE_WHEEL;
        r_event.delta = delta;

        CallEvent(r_event);
        result = true;
        break;
    }
	}

    return result;
}

#endif