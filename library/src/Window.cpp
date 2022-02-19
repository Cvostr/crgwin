#include <base/Window.hpp>

using namespace crgwin;

Window::Window(const WindowCreateInfo& create_info) :
	_title(create_info.title),
	_create_info(create_info),
	_client_size(create_info.size),
	_closed(false),
	_visible(false)
{

}

const std::string& Window::GetTitle() const {
	return _title;
}

const crgwin::ivec2& Window::GetSize() const {
	return _client_size;
}