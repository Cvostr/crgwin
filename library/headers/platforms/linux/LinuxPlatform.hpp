#pragma once

#include <base/Platform.hpp>

struct _XDisplay;
typedef struct _XDisplay X11Display;
typedef unsigned long X11Window;

namespace crgwin{
    class LinuxPlatform : public Platform{
    public:

        static void Init();

        static void Tick();

        static X11Display* GetDisplay();


    };
}