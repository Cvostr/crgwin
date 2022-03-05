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

}

void crgwin::LinuxWindow::Resize(const crgwin::ivec2& size){

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

void crgwin::LinuxWindow::Minimize(){

}

void crgwin::LinuxWindow::Maximize(){

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
            //if (event->xproperty.atom == xAtomWmState){

            //}
        }
    }
}

#endif