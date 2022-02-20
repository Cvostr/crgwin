#pragma once

#include <base/Window.hpp>

namespace crgwin {
	class UWPWindow : public Window {
	private:
		
	public:

		UWPWindow(const WindowCreateInfo& create_info);

		~UWPWindow();

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