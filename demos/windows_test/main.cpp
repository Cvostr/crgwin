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
		win->SetEventsHandler(EVENTS_HANDLER(App::EventsHandler));

		while (true) {
			crgwin::Tick();
		}
	}

	void EventsHandler(crgwin::WindowEvent event) {
		if (event.type == crgwin::WindowEventType::EVENT_KEYDOWN) {
			std::cout << "Key pressed " << event.key << std::endl;
			if (event.key == crgKeyCode::KEY_CODE_B)
				win->Resize(crgwin::ivec2(1366, 768));
			if (event.key == crgKeyCode::KEY_CODE_M)
				win->Minimize();
			if (event.key == crgKeyCode::KEY_CODE_N)
				win->Maximize();
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