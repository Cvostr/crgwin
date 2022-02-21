#pragma once

#include <base/Window.hpp>

namespace crgwin{

void Init();

Window* CreateWindow(WindowCreateInfo& create_info);

void Tick();

}