#pragma once

#include <string>
#include <base/cgVec2.hpp>

#define WINDOW_DEFAULT_POS -1000

namespace crgwin {

	struct WindowCreateInfo {
		/// <summary>
		/// Window title
		/// </summary>
		std::string title;
		/// <summary>
		/// Window start size
		/// </summary>
		crgwin::ivec2 size;
		/// <summary>
		/// Window minimum allowed size
		/// </summary>
		crgwin::ivec2 min_size;
		/// <summary>
		/// Window maximum allowed size
		/// </summary>
		crgwin::ivec2 max_size;
		/// <summary>
		/// window start position
		/// </summary>
		crgwin::ivec2 position;
		/// <summary>
		/// is window fullscreen on start
		/// </summary>
		bool fullscreen;
		/// <summary>
		/// enable or disable resize
		/// </summary>
		bool resize;

		WindowCreateInfo() {
			title = "Title";
			size = crgwin::ivec2(1280, 720);
			min_size = crgwin::ivec2(640, 480);
			max_size = crgwin::ivec2(8192, 4096);
			position = crgwin::ivec2(WINDOW_DEFAULT_POS, WINDOW_DEFAULT_POS);
			fullscreen = false;
			resize = true;
		}
	};

	class Window {
	protected:
		bool _minimized;
		bool _maximized;
		bool _closed;
		bool _visible;
		std::string _title;
		crgwin::ivec2 _client_size;

		WindowCreateInfo _create_info;

	public:

		explicit Window(const WindowCreateInfo& create_info);

		virtual ~Window(){}

		const std::string& GetTitle() const;

		virtual void SetTitle(const std::string& title) = 0;

		const crgwin::ivec2& GetSize() const;

		virtual void Show() = 0;

		virtual void Hide() = 0;

		virtual void Minimize() = 0;

		virtual void Maximize() = 0;

		virtual void Close() = 0;
	};
}