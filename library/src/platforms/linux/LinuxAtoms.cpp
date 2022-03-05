#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <platforms/linux/LinuxAtoms.hpp>
#include <platforms/linux/LinuxPlatform.hpp>

::Atom xAtomDeleteWindow;
::Atom xAtomXdndEnter;
::Atom xAtomXdndPosition;
::Atom xAtomXdndLeave;
::Atom xAtomXdndDrop;
::Atom xAtomXdndActionCopy;
::Atom xAtomXdndStatus;
::Atom xAtomXdndSelection;
::Atom xAtomXdndFinished;
::Atom xAtomXdndAware;
::Atom xAtomWmState;
::Atom xAtomWmStateHidden;
::Atom xAtomWmStateMaxVert;
::Atom xAtomWmStateMaxHorz;
::Atom xAtomWmWindowOpacity;
::Atom xAtomWmName;
::Atom xAtomClipboard;


void crgwin::InitAtoms(){
    auto display = LinuxPlatform::GetDisplay();
    if (!display)
        return;

    xAtomDeleteWindow = ::XInternAtom(display, "WM_DELETE_WINDOW", 0);
    xAtomXdndEnter = ::XInternAtom(display, "XdndEnter", 0);
	xAtomXdndPosition = ::XInternAtom(display, "XdndPosition", 0);
	xAtomXdndLeave = ::XInternAtom(display, "XdndLeave", 0);
	xAtomXdndDrop = ::XInternAtom(display, "XdndDrop", 0);
    xAtomXdndActionCopy = ::XInternAtom(display, "XdndActionCopy", 0);
    xAtomXdndStatus = ::XInternAtom(display, "XdndStatus", 0);
    xAtomXdndSelection = ::XInternAtom(display, "XdndSelection", 0);
    xAtomXdndFinished = ::XInternAtom(display, "XdndFinished", 0);
    xAtomXdndAware = ::XInternAtom(display, "XdndAware", 0);
    xAtomWmState = ::XInternAtom(display, "_NET_WM_STATE", 1);
	xAtomWmStateHidden = ::XInternAtom(display, "_NET_WM_STATE_HIDDEN", 0);
	xAtomWmStateMaxHorz = ::XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", 0);
	xAtomWmStateMaxVert = ::XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", 0);
	xAtomWmWindowOpacity = ::XInternAtom(display, "_NET_WM_WINDOW_OPACITY", 0);
	xAtomWmName = ::XInternAtom(display, "_NET_WM_NAME", 0);
	xAtomClipboard = ::XInternAtom(display, "CLIPBOARD", 0);
}

::Atom& crgwin::GetDeleteWindowAtom(){
    return xAtomDeleteWindow;
}

::Atom crgwin::GetWmStateAtom(){
    return xAtomWmState;
}

::Atom crgwin::GetWmStateMaxHorzAtom(){
    return xAtomWmStateMaxHorz;
}

::Atom crgwin::GetWmStateMaxVertAtom(){
    return xAtomWmStateMaxVert;
}

::Atom crgwin::GetWmStateHiddenAtom(){
    return xAtomWmStateHidden;
}

#endif