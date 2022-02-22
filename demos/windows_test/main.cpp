#include <crgwin.hpp>
#include <iostream>

class App {
private:
	crgwin::Window* win;
public:

	App() {
		crgwin::WindowCreateInfo cr_info;
		cr_info.title = "Sample �������";
		cr_info.resize = false;

		win = crgwin::CreateWindow(cr_info);
		win->Show();
		win->SetEventsHandler(std::bind(&App::EventsHandler, this, std::placeholders::_1));

		while (true) {
			crgwin::Tick();
		}
	}

	void EventsHandler(crgwin::WindowEvent event) {
		if (event.type == crgwin::WindowEventType::EVENT_KEYDOWN) {
			std::cout << "Key pressed " << event.key << std::endl;
			if (event.key == crgKeyCode::KEY_CODE_B)
				win->Resize(crgwin::ivec2(1366, 768));
		}
		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_MOVED) {
			std::cout << "mouse moved " << event.coord.x << " " << event.coord.y << std::endl;
		}
	}
};

int main(int argc, char** argv) {
	
	//cr_info.borderless = true;

	crgwin::Init();


	App* app = new App();

	
}