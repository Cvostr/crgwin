#include <base/Window.hpp>

using namespace crgwin;

Window::Window(const WindowCreateInfo& create_info) :
	_title(create_info.title),
	_create_info(create_info),
	_client_size(create_info.size),
	_state(WindowState::STATE_DEFAULT),
	_closed(false),
	_visible(false),
	_resizing(false),
	_focused(false)
{

}

const std::string& Window::GetTitle() const {
	return _title;
}

const crgwin::ivec2& Window::GetSize() const {
	return _client_size;
}

WindowState Window::GetState() const {
	return _state;
}

bool Window::IsVisible() const {
	return _visible;
}

bool Window::IsClosed() const {
	return _closed;
}

bool Window::IsFocused() const {
	return _focused;
}

void Window::SetEventsHandler(WindowEventHandler handler) {
	_events_handler = handler;
}

void Window::CallEvent(const WindowEvent& event) {
	_events_handler(event);
}