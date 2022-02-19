#include <platforms/win32/Win32Window.hpp>
#include <platforms/win32/Win32Platform.hpp>

int main(int argc, char** argv) {
	crgwin::WindowCreateInfo cr_info;
	cr_info.title = "Sample Образец";
	cr_info.resize = false;

	crgwin::Win32Platform::RegisterWindowClass();

	crgwin::Window* w = new crgwin::Win32Window(cr_info);
	w->Show();

	while (true) {
		crgwin::Win32Platform::Tick();
	}
}