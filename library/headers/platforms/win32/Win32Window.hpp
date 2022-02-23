#pragma once

#include <base/Window.hpp>
#include "Win32Platform.hpp"

namespace crgwin {
	class Win32Window : public Window {
	private:
		HWND win32_handle;

		bool WndProcInput(UINT msg, WPARAM wParam, LPARAM lParam);
		void UpdateClientSize();

		unsigned int GetWin32Style();
		unsigned int GetWin32ExStyle();
	public:

		Win32Window(const WindowCreateInfo& create_info);

		~Win32Window();

		WindowHandle GetNativeHandle() const;

		LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

		void SetTitle(const std::string& title);

		crgwin::ivec2 GetWindowPos();

		void SetWindowPos(crgwin::ivec2 pos);

		void Resize(const crgwin::ivec2& size);

		void SetResizeable(bool resizeable);

		void SetBorderless(bool borderless);

		void Show();

		void Hide();

		void Minimize();

		void Maximize();

		void Close();

		void Restore();
	};
}