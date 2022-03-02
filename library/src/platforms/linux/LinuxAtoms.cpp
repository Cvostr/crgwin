#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <platforms/linux/LinuxAtoms.hpp>

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

#endif