#pragma once

#include <X11/Xlib.h>
#include <X11/Xatom.h>

namespace crgwin{

    void InitAtoms();

    ::Atom GetDeleteWindowAtom();
}