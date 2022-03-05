#include <platforms/linux/LinuxWindow.hpp>

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <platforms/linux/LinuxAtoms.hpp>

void crgwin::LinuxWindow::ProcessInputEvents(void* pEvent){
    ::XEvent* event = static_cast<::XEvent*>(pEvent); 
    WindowEvent r_event;
    switch (event->type)
	{
        case ButtonPress:{
            r_event.type = WindowEventType::EVENT_MOUSE_BTN_DOWN;
            XButtonPressedEvent* mouse_event = &event->xbutton;
            switch (mouse_event->button){
            case Button1:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_LEFT;
                break;
            case Button2:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_RIGHT;
                break;
            case Button3:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_MIDDLE;
                break;
            default:
                return;
            }
            CallEvent(r_event);
            break;
        }
        case ButtonRelease: {
            r_event.type = WindowEventType::EVENT_MOUSE_BTN_UP;
            XButtonPressedEvent* mouse_event = &event->xbutton;
            switch (mouse_event->button){
            case Button1:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_LEFT;
                break;
            case Button2:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_RIGHT;
                break;
            case Button3:
                r_event.mouse_button = crgMouseButton::MOUSE_BUTTON_MIDDLE;
                break;
            default:
                return;
            }
            CallEvent(r_event);
            break;
        }
        case KeyPress:
            r_event.type = WindowEventType::EVENT_KEYDOWN;
            CallEvent(r_event);
            //&event.xkey
			break;
		case KeyRelease:
            r_event.type = WindowEventType::EVENT_KEYUP;
            CallEvent(r_event);
            //&event.xkey
			break;

    }
}

#endif