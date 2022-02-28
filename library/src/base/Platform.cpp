#include <base/Platform.hpp>

std::vector<crgwin::Window*> crgwin::Platform::windows;

void crgwin::Platform::RegisterWindow(Window* window) {
    if (GetByHandle(window->GetNativeHandle()))
        return;

    windows.push_back(window);
}
void crgwin::Platform::UnregisterWindow(Window* window) {
    if (GetByHandle(window->GetNativeHandle())) {
        auto it = std::remove(windows.begin(), windows.end(), window);
        windows.pop_back();
    }
}
crgwin::Window* crgwin::Platform::GetByHandle(WindowHandle handle) {
    for (auto& win : windows) {
        if (win->GetNativeHandle() == handle)
            return win;
    }
    return nullptr;
}
