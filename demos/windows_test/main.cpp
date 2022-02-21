#include <crgwin.hpp>
#include <iostream>

void method(crgKeyCode code) {
	std::cout << code << std::endl;
}

int main(int argc, char** argv) {
	crgwin::WindowCreateInfo cr_info;
	cr_info.title = "Sample �������";
	cr_info.resize = false;
	//cr_info.borderless = true;

	crgwin::Init();

	crgwin::Window* w = crgwin::CreateWindow(cr_info);
	w->Show();

	w->keydown = Function<void, crgKeyCode>(method);

	while (true) {
		crgwin::Tick();
	}
}