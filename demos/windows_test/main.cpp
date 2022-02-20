#include <platforms/win32/Win32Window.hpp>
#include <platforms/win32/Win32Platform.hpp>
#include <iostream>

void method(int dx, int dy) {
	std::cout << dx << " " << dy;
}

int main(int argc, char** argv) {
	crgwin::WindowCreateInfo cr_info;
	cr_info.title = "Sample Образец";
	cr_info.resize = false;
	//cr_info.borderless = true;

	crgwin::Win32Platform::RegisterWindowClass();

	crgwin::Window* w = new crgwin::Win32Window(cr_info);
	w->Show();

	w->mouse = Function<void, int, int>(method);

	while (true) {
		crgwin::Win32Platform::Tick();
	}
}