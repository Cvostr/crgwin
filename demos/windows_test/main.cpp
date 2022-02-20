#include <crgwin.hpp>
#include <iostream>

void method(int dx, int dy) {
	std::cout << dx << " " << dy;
}

int main(int argc, char** argv) {
	crgwin::WindowCreateInfo cr_info;
	cr_info.title = "Sample �������";
	cr_info.resize = false;
	//cr_info.borderless = true;

	crgwin::Init();

	crgwin::Window* w = crgwin::CreateWindow(cr_info);
	w->Show();

	w->mouse = Function<void, int, int>(method);

	while (true) {
		//crgwin::Win32Platform::Tick();
	}
}