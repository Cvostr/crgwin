#pragma once

#include <base/Window.hpp>
#include "LinuxPlatform.hpp"

namespace crgwin {
	class LinuxWindow : public Window {
	private:
		X11Window _handle;

		bool IsMapped();

		void Minimize(bool dir);

		void Maximize(bool dir);
	public:
		LinuxWindow(const WindowCreateInfo& create_info);

		~LinuxWindow();

		void ProcessEvent(void* pEvent);

		void ProcessInputEvents(void* pEvent);

		WindowHandle GetNativeHandle() const;

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