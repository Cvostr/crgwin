#include <crgwin.hpp>

#ifdef __linux__
#include <platforms/linux/LinuxPlatform.hpp>
#include <platforms/linux/LinuxWindow.hpp>
#endif

#ifdef _WIN32
#include <platforms/win32/Win32Window.hpp>
#endif

void crgwin::Init(){
    #ifdef _WIN32
    crgwin::Win32Platform::RegisterWindowClass();
    #endif

    #ifdef __linux__
    crgwin::LinuxPlatform::Init();
    #endif
}

crgwin::Window* crgwin::CreateWindow(WindowCreateInfo& create_info){
#ifdef _WIN32
    return new Win32Window(create_info);
#endif

#ifdef __linux__
return new LinuxWindow(create_info);
#endif
}

void crgwin::Tick() {
#ifdef _WIN32
    crgwin::Win32Platform::Tick();
#endif

#ifdef __linux__
    crgwin::LinuxPlatform::Tick();
#endif
}