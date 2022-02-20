#pragma once

#include <base/Platform.hpp>
#include <base/CpuInfo.hpp>
#include <vector>

struct HINSTANCE__;
struct HWND__;

typedef void* HANDLE;
typedef HINSTANCE__* HINSTANCE;
typedef HINSTANCE HMODULE;
typedef HWND__* HWND;

typedef unsigned int UINT;
typedef unsigned __int64 UINT_PTR;
typedef __int64 LONG_PTR;
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#define WIN32_WIN_CLASS_W L"crgwin_window"
#define WIN32_WIN_CLASS "crgwin_window"

namespace crgwin {

	class Win32Window;

	class Win32Platform : public crgwin::Platform {
	private:
		static std::vector<Win32Window*> windows;
	public:
		static HINSTANCE GetInstance();
		static void RegisterWindowClass();
		static void Tick();

		static void RegisterWindow(Win32Window* window);
		static void UnregisterWindow(Win32Window* window);
		static Win32Window* GetByHWND(HWND hwnd);
	};
}