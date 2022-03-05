#include <platforms/linux/LinuxPlatform.hpp>
#include <platforms/linux/LinuxWindow.hpp>

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <platforms/linux/LinuxAtoms.hpp>

X11Display* x11_display = nullptr;
XIM IM = nullptr;
XIC IC = nullptr;

void crgwin::LinuxPlatform::Init(){
    ::XInitThreads();
    //opening display
    x11_display = ::XOpenDisplay(nullptr);

    if (::XSupportsLocale())
	{
		::XSetLocaleModifiers("@im=none");
		IM = ::XOpenIM(x11_display, nullptr, nullptr, nullptr);
		IC = ::XCreateIC(IM, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, nullptr);
	}

    InitAtoms();
}

X11Display* crgwin::LinuxPlatform::GetDisplay(){
    return x11_display;
}

XIC crgwin::LinuxPlatform::GetIC(){
    return IC;
}

void crgwin::LinuxPlatform::Tick(){
    if (!x11_display)
        return;

    while (::XPending(x11_display) > 0){
        ::XEvent event;
		::XNextEvent(x11_display, &event);

        if (::XFilterEvent(&event, 0))
			continue;

        WindowHandle window_handle = (WindowHandle)event.xclient.window;
        LinuxWindow* window = static_cast<LinuxWindow*>(Platform::GetByHandle(window_handle));

        if(window){
            window->ProcessEvent(&event);
        }
    }
}

#endif