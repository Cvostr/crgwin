#include <crgwin.hpp>
#include <iostream>

class App {
private:
	crgwin::Window* win;
	bool running;
public:

	App() {
		crgwin::WindowCreateInfo cr_info;
		cr_info.title = "Sample �������";
		cr_info.resize = false;

		win = crgwin::CreateWindow(cr_info);
		win->Show();
		win->SetEventsHandler(EVENTS_HANDLER(App::EventsHandler));

		running = true;
		while (running) {
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
			if (event.key == crgKeyCode::KEY_CODE_R)
				win->SetResizeable(true);
			if (event.key == crgKeyCode::KEY_CODE_K)
				win->SetBorderless(true);
		}
		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_MOVED) {
			//std::cout << "mouse moved " << event.coord.x << " " << event.coord.y << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_FOCUS_GAIN) {
			std::cout << "focus gained" << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_FOCUS_LOST) {
			std::cout << "focus lost" << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_SIZE_CHANGED) {
			std::cout << "window resized" << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_STATE_CHANGED) {
			if(event.state == crgwin::WindowState::STATE_MINIMIZED)
				std::cout << "window minimized" << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_WHEEL) {
			std::cout << "mouse wheel " << event.delta << std::endl;
		}
		if (event.type == crgwin::WindowEventType::EVENT_CLOSED) {
			std::cout << "window closed" << std::endl;
			running = false;
		}
	}
};

int main(int argc, char** argv) {
	
	crgwin::Init();


	App* app = new App();

	
}