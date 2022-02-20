#include <platforms/linux/LinuxPlatform.hpp>

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>

X11Display* x11_display = nullptr;

void crgwin::LinuxPlatform::Init(){
    ::XInitThreads();
    //opening display
    x11_display = ::XOpenDisplay(nullptr);
}

X11Display* crgwin::LinuxPlatform::GetDisplay(){
    return x11_display;
}

#endif