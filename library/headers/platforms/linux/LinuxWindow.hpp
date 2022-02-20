#pragma once

#include <base/Window.hpp>
#include "LinuxPlatform.hpp"

namespace crgwin {
	class LinuxWindow : public Window {
	private:
		X11Window _handle;
	public:
		LinuxWindow(const WindowCreateInfo& create_info);

		~LinuxWindow();

		void SetTitle(const std::string& title);

		crgwin::ivec2 GetWindowPos();

		void SetWindowPos(crgwin::ivec2 pos);

		void Show();

		void Hide();

		void Minimize();

		void Maximize();

		void Close();
	};
}