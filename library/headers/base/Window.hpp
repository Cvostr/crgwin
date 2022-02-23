#pragma once

#include <string>
#include <base/cgVec2.hpp>
#include <base/InputConstants.hpp>
#include <functional>

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
		/// is window borderless on start
		/// </summary>
		bool borderless;
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
			borderless = false;
			resize = true;
		}
	};

	enum class WindowState {
		STATE_DEFAULT,
		STATE_MAXIMIZED,
		STATE_MINIMIZED
	};

	enum class WindowEventType {
		EVENT_NONE = 0,
		EVENT_KEYDOWN,
		EVENT_KEYUP,
		EVENT_MOUSE_BTN_DOWN,
		EVENT_MOUSE_BTN_UP,
		EVENT_MOUSE_MOVED,
		EVENT_STATE_CHANGED,
		EVENT_SIZE_CHANGED
	};
	
	class WindowEvent {
	public:

		WindowEvent() :
			type(WindowEventType::EVENT_NONE), coord(0, 0) 
		{}

		WindowEventType type;
		union {
			crgKeyCode key;
			crgMouseButton mouse_button;
			WindowState state;
			ivec2 coord;
		};
	};

	typedef void* WindowHandle;
	typedef std::function<void(WindowEvent)> WindowEventHandler;

#define EVENTS_HANDLER(x) std::bind(&x, this, std::placeholders::_1)

	class Window {
	protected:
		WindowState _state;
		bool _closed;
		bool _visible;
		bool _resizing;
		bool _focused;
		std::string _title;
		crgwin::ivec2 _client_size;

		WindowCreateInfo _create_info;

		WindowEventHandler _events_handler;

		void CallEvent(const WindowEvent& event);
	public:

		explicit Window(const WindowCreateInfo& create_info);

		virtual ~Window(){}
		/// <summary>
		/// Gets current window title
		/// </summary>
		/// <returns>window title string</returns>
		const std::string& GetTitle() const;
		/// <summary>
		/// Set new title to window
		/// </summary>
		/// <param name="title">- new title string</param>
		virtual void SetTitle(const std::string& title) = 0;
		/// <summary>
		/// Get size of window client area
		/// </summary>
		/// <returns></returns>
		const crgwin::ivec2& GetSize() const;
		/// <summary>
		/// Resize window client area
		/// </summary>
		/// <param name="size">- new size of client area</param>
		virtual void Resize(const crgwin::ivec2& size) = 0;
		/// <summary>
		/// Gets current window position
		/// </summary>
		/// <returns></returns>
		virtual crgwin::ivec2 GetWindowPos() = 0;
		/// <summary>
		/// Move window in screen
		/// </summary>
		/// <param name="pos">- new position for window</param>
		virtual void SetWindowPos(crgwin::ivec2 pos) = 0;
		/// <summary>
		/// Gets current window state
		/// </summary>
		/// <returns></returns>
		WindowState GetState() const;
		/// <summary>
		/// Gets a value that indicates whether a window is visible
		/// </summary>
		/// <returns></returns>
		bool IsVisible() const;
		/// <summary>
		/// Checks if window is closed.
		/// </summary>
		/// <returns></returns>
		bool IsClosed() const;
		/// <summary>
		/// Determines whether this window is focused
		/// </summary>
		/// <returns></returns>
		bool IsFocused() const;
		/// <summary>
		/// Shows the window
		/// </summary>
		virtual void Show() = 0;
		/// <summary>
		/// Hides the window
		/// </summary>
		virtual void Hide() = 0;
		/// <summary>
		/// Minimize window to taskbar
		/// </summary>
		virtual void Minimize() = 0;
		/// <summary>
		/// Maximize window
		/// </summary>
		virtual void Maximize() = 0;
		/// <summary>
		/// Destroy window
		/// </summary>
		virtual void Close() = 0;
		/// <summary>
		/// Restore window
		/// </summary>
		virtual void Restore() = 0;

		void SetEventsHandler(WindowEventHandler handler);
		/// <summary>
		/// Get platform dependent window handler pointer
		/// </summary>
		/// <returns></returns>
		virtual WindowHandle GetNativeHandle() const = 0;
	};
}