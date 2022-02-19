#pragma once

#include <base/Window.hpp>
#include "Win32Platform.hpp"

namespace crgwin {
	class Win32Window : public Window {
	private:
		HWND win32_handle;
	public:

		Win32Window(const WindowCreateInfo& create_info);

		~Win32Window();

		HWND GetHWND() const;

		LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

		void SetTitle(const std::string& title);

		void Show();

		void Hide();

		void Minimize();

		void Maximize();

		void Close();
	};
}