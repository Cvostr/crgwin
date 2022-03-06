#ifdef __linux__

#include <platforms/linux/LinuxWindow.hpp>
#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <platforms/linux/LinuxAtoms.hpp>

#define _NET_WM_STATE_REMOVE 0L // remove/unset property
#define _NET_WM_STATE_ADD 1L // add/set property
#define _NET_WM_STATE_TOGGLE 2L // toggle property

crgwin::LinuxWindow::LinuxWindow(const WindowCreateInfo& create_info) : Window(create_info) {
    auto display = LinuxPlatform::GetDisplay();
    if (!display)
        return;

    int screen = XDefaultScreen(display);
	auto rootWindow = XRootWindow(display, screen);

    long visualMask = VisualScreenMask;
	int numberOfVisuals;
	XVisualInfo vInfoTemplate = {};
	vInfoTemplate.screen = screen;
	XVisualInfo* visualInfo = ::XGetVisualInfo(display, visualMask, &vInfoTemplate, &numberOfVisuals);

    Colormap colormap = ::XCreateColormap(display, rootWindow, visualInfo->visual, AllocNone);
    
    XSetWindowAttributes windowAttributes = {};
	windowAttributes.colormap = colormap;
	windowAttributes.background_pixel = XBlackPixel(display, screen);
	windowAttributes.border_pixel = XBlackPixel(display, screen);
	windowAttributes.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

    _handle = ::XCreateWindow(
		display, ::XRootWindow(display, screen), 100, 100,
		create_info.size.x, create_info.size.y, 0, visualInfo->depth, InputOutput,
		visualInfo->visual,
		CWBackPixel | CWBorderPixel | CWEventMask | CWColormap, &windowAttributes);

    SetTitle(create_info.title);

    long eventMask =
			ExposureMask | FocusChangeMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask |
			EnterWindowMask | LeaveWindowMask |
			VisibilityChangeMask | ExposureMask |
			PointerMotionMask | ButtonMotionMask |
			StructureNotifyMask | PropertyChangeMask;

	::XSelectInput(display, _handle, eventMask);

    ::XSetWMProtocols(display, _handle, &GetDeleteWindowAtom(), 1);

    if(create_info.borderless){

    }

    if(!create_info.resize){
        //block resizing
        SetSizeHints(create_info.size, create_info.size);
    }

    ::Atom wmState = ::XInternAtom(display, "_NET_WM_STATE", 0);
    std::vector<::Atom> states;
	

    if(create_info.fullscreen){
        ::Atom wmStateFullscreen = ::XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", 0);
        states.push_back(wmStateFullscreen);
    }

    ::XChangeProperty(display, _handle, wmState, (::Atom)4, 32, PropModeReplace, (unsigned char*)states.data(), states.size());
    //register window in list
    Platform::RegisterWindow(this);
    //sync x11
    ::XFlush(display);
	::XSync(display, 0);
	::XFree(visualInfo);
}

crgwin::LinuxWindow::~LinuxWindow(){

}

bool crgwin::LinuxWindow::IsMapped(){
    X11Display* display = LinuxPlatform::GetDisplay();
    if (!display || !_handle){
        return false;
    }
    ::XWindowAttributes xwa;
	::XGetWindowAttributes(display, _handle, &xwa);
	return xwa.map_state != IsUnmapped;
}

void crgwin::LinuxWindow::SetSizeHints(crgwin::ivec2 min, crgwin::ivec2 max){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::XSizeHints hints;
		hints.flags = PMinSize | PMaxSize;
		hints.min_height = min.y;
		hints.max_height = max.y;
		hints.min_width = min.x;
		hints.max_width = max.x;
		::XSetNormalHints(display, _handle, &hints);
    }
}

crgwin::WindowHandle crgwin::LinuxWindow::GetNativeHandle() const {
    return (WindowHandle)_handle;
}

void crgwin::LinuxWindow::SetTitle(const std::string& title){
    if(_handle){
        ::XStoreName(LinuxPlatform::GetDisplay(), _handle, title.c_str());
    }
}

crgwin::ivec2 crgwin::LinuxWindow::GetWindowPos(){
    X11Display* display = LinuxPlatform::GetDisplay();
    if (!display)
        return crgwin::ivec2(0, 0);
	::XWindowAttributes xwa;
	::XGetWindowAttributes(display, _handle, &xwa);
	return crgwin::ivec2(xwa.x, xwa.y);
}

void crgwin::LinuxWindow::SetWindowPos(crgwin::ivec2 pos){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::XMoveWindow(display, _handle, pos.x, pos.y);
	    ::XFlush(display);
    }
}

void crgwin::LinuxWindow::Resize(const crgwin::ivec2& size){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ivec2 old_pos = GetWindowPos();
        _client_size = size;

        if(!_create_info.resize){
            SetSizeHints(size, size);
        }

	    ::XResizeWindow(display, _handle, size.x, size.y);
	    ::XMoveWindow(display, _handle, old_pos.x, old_pos.y);
	    ::XFlush(display);
    }
}

void crgwin::LinuxWindow::Show(){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::XMapWindow(display, _handle);
        ::XFlush(display);
    }
}

void crgwin::LinuxWindow::Hide(){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::XUnmapWindow(display, _handle);
    }
}

#define X11_DefaultRootWindow(dpy) (((&((::_XPrivDisplay)(dpy))->screens[(((::_XPrivDisplay)(dpy))->default_screen)]))->root)

void crgwin::LinuxWindow::Minimize(bool dir){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::Atom wmChange = ::XInternAtom(display, "WM_CHANGE_STATE", 0);
        ::XEvent event = {};
        event.type = ClientMessage;
        event.xclient.window = _handle;
        event.xclient.message_type = wmChange;
        event.xclient.format = 32;
        event.xclient.data.l[0] = dir ? 3L : 1L; //minimized state

        XSendEvent(display, X11_DefaultRootWindow(display), 0, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        if(dir)
            _state = WindowState::STATE_MINIMIZED;
    }
}

void crgwin::LinuxWindow::Maximize(bool dir){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::Atom wmState = ::XInternAtom(display, "_NET_WM_STATE", 0);
	    ::Atom wmMaxHorz = ::XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", 0);
	    ::Atom wmMaxVert = ::XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", 0);

        bool mapped = IsMapped();
        if (mapped){
            ::XEvent event = {};
            event.type = ClientMessage;
            event.xclient.window = _handle;
            event.xclient.message_type = wmState;
            event.xclient.format = 32;
            event.xclient.data.l[0] = dir ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
            event.xclient.data.l[1] = wmMaxHorz;
            event.xclient.data.l[2] = wmMaxVert;

		    XSendEvent(display, X11_DefaultRootWindow(display), 0, SubstructureRedirectMask | SubstructureNotifyMask, &event);
        }else{
            ::Atom states[2];
            states[0] = wmMaxVert;
            states[1] = wmMaxHorz;
            ::XChangeProperty(display, _handle, wmState, (::Atom)4, 32, PropModeReplace, (unsigned char*)states, 2);
        }

        if(dir)
            _state = WindowState::STATE_MAXIMIZED;
    }
}

void crgwin::LinuxWindow::Minimize(){
    Minimize(true);
}

void crgwin::LinuxWindow::Maximize(){
    Maximize(true);
}

void crgwin::LinuxWindow::Close(){
    X11Display* display = LinuxPlatform::GetDisplay();
    if(_handle && display){
        ::XDestroyWindow(display, _handle);
        Platform::UnregisterWindow(this);
    }
}

void crgwin::LinuxWindow::Restore() {

}

void crgwin::LinuxWindow::SetResizeable(bool resizeable){

}

void crgwin::LinuxWindow::SetBorderless(bool borderless){

}

void crgwin::LinuxWindow::ProcessEvent(void* pEvent){
    ::XEvent* event = static_cast<::XEvent*>(pEvent); 
    WindowEvent r_event;

    ProcessInputEvents(pEvent);

    switch (event->type)
	{
        case ClientMessage : {
            if ((::Atom)event->xclient.data.l[0] == GetDeleteWindowAtom()){
                Close();
                r_event.type = WindowEventType::EVENT_CLOSED;
                CallEvent(r_event);
            }
            break;
        }
        case FocusIn:
                //update flag
                _focused = true;
				// Update input context focus
				::XSetICFocus(LinuxPlatform::GetIC());
                //raise event
                r_event.type = WindowEventType::EVENT_FOCUS_GAIN;
                CallEvent(r_event);
                break;
        case FocusOut:
                //update flag
                _focused = false;
				// Update input context focus
				::XUnsetICFocus(LinuxPlatform::GetIC());
                //raise event
                r_event.type = WindowEventType::EVENT_FOCUS_LOST;
                CallEvent(r_event);
                break;
                
				
        case PropertyNotify : {
            if (event->xproperty.atom == GetWmStateAtom()){
                ::Atom type;
				int format;
				unsigned long count, bytesRemaining;
				unsigned char* data = nullptr;
                X11Display* display = LinuxPlatform::GetDisplay();
				const int result = ::XGetWindowProperty(display, event->xproperty.window, GetWmStateAtom(), 0, 1024, 0, AnyPropertyType, &type, &format, &count, &bytesRemaining, &data);
				if (result == Success){
                    ::Atom* atoms = (::Atom*)data;
                    bool foundHorz = false;
					bool foundVert = false;
                    for (unsigned long i = 0; i < count; i++){
                        if (atoms[i] == GetWmStateMaxHorzAtom())
							foundHorz = true;
						if (atoms[i] == GetWmStateMaxVertAtom())
							foundVert = true;
                        if (foundVert && foundHorz){
                            if (event->xproperty.state == PropertyNewValue){
                                if(_state != WindowState::STATE_MAXIMIZED){
                                    _state = WindowState::STATE_MAXIMIZED;
                                    r_event.type = WindowEventType::EVENT_STATE_CHANGED;
                                    r_event.state = WindowState::STATE_MAXIMIZED;
                                    CallEvent(r_event);
                                }
							}
                        } else if (atoms[i] == GetWmStateHiddenAtom()){
                            if (event->xproperty.state == PropertyNewValue){
                                if(_state != WindowState::STATE_MINIMIZED){
                                    _state = WindowState::STATE_MINIMIZED;
                                    r_event.type = WindowEventType::EVENT_STATE_CHANGED;
                                    r_event.state = WindowState::STATE_MINIMIZED;
                                    CallEvent(r_event);
                                }
							}
                        } else {
							// Restored
							_state = WindowState::STATE_DEFAULT;
                            r_event.type = WindowEventType::EVENT_MOUSE_WHEEL;
                            CallEvent(r_event);
						}
                    }
                }
            }
            break;
        }
    }
}

#endif