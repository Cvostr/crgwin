# CRossplatform Game WINdow

is little cross-platform development library for creating and operating game windows. Currently it supports Windows, Linux (X11) platforms. Planning to support Xbox (GDK) and Android.

Here is simple example creating empty window and events listening

```cpp
class  App {
private:
	crgwin::Window* win;
	bool  running;
public:

	App() {
		crgwin::WindowCreateInfo  cr_info;
		cr_info.title  =  "Sample window";
		cr_info.resize = false;

		win = crgwin::CreateWindow(cr_info);
		win->Show();
		win->SetEventsHandler(EVENTS_HANDLER(App::EventsHandler));
		running = true;
		
		while (running) {
			crgwin::Tick();
		}
	}

	void  EventsHandler(crgwin::WindowEvent  event) {
		if (event.type == crgwin::WindowEventType::EVENT_KEYDOWN) {
			std::cout  <<  "Key pressed "  <<  event.key  <<  std::endl;

			if (event.key == crgKeyCode::KEY_CODE_B)
				win->Resize(crgwin::ivec2(1366, 768));

			if (event.key == crgKeyCode::KEY_CODE_M)
				win->Minimize();

			if (event.key == crgKeyCode::KEY_CODE_N)
				win->Maximize();

			if (event.key == crgKeyCode::KEY_CODE_R)
				win->SetResizeable(true);

			if (event.key == crgKeyCode::KEY_CODE_K) {
				win->SetBorderless(true);
				std::cout  <<  "Window is borderless, new client size "  <<  win->GetSize().x  <<  " "  <<  win->GetSize().y  <<  std::endl;
			}

			if (event.key == crgKeyCode::KEY_CODE_G) {
				crgwin::MessageDialogDesc  desc = {};
				desc.dialogTitle  =  "Sample dialog";
				desc.dialogMessage  =  "Sample dialog message";
				crgwin::DialogUserAction  action;
				crgwin::MessageDialog(&desc, action, win);
			}

			if (event.key == crgKeyCode::KEY_CODE_F) {
				crgwin::FileDialogDesc  desc = {};
				desc.extensions.push_back(crgwin::FileExtensionDesc("Text file", "*.txt"));
				desc.extensions.push_back(crgwin::FileExtensionDesc("Log file", "*.log"));
				desc.extensions.push_back(crgwin::FileExtensionDesc());
				desc.baseFileName  =  "test.txt";
				desc.initialDir  =  "c:\\Users";
				std::string  result;
				crgwin::OpenFileDialog(&desc, result, win);
			}
		}

		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_BTN_DOWN) {
			std::cout  <<  "mouse btn down "  <<  event.mouse_button  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_BTN_UP) {
			std::cout  <<  "mouse btn up "  <<  event.mouse_button  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_MOVED) {
			std::cout << "mouse moved " << event.coord.x << " " << event.coord.y << std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_FOCUS_GAIN) {
			std::cout  <<  "focus gained"  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_FOCUS_LOST) {
			std::cout  <<  "focus lost"  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_SIZE_CHANGED) {
			std::cout  <<  "window resized"  <<  std::endl;
			std::cout  <<  "new client size "  <<  win->GetSize().x  <<  " "  <<  		win->GetSize().y  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_STATE_CHANGED) {
			if(event.state == crgwin::WindowState::STATE_MINIMIZED)
				std::cout  <<  "window minimized"  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_MOUSE_WHEEL) {
			std::cout  <<  "mouse wheel "  <<  event.delta  <<  std::endl;
		}

		if (event.type == crgwin::WindowEventType::EVENT_CLOSED) {
			std::cout  <<  "window closed"  <<  std::endl;
			running = false;
		}
	}
};
int main(int  argc, char**  argv) {
	crgwin::Init();
	App* app = new  App();
}
```



