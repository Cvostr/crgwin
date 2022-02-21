#pragma once

#include "BatteryInfo.hpp"
#include "CpuInfo.hpp"
#include "MemoryInfo.hpp"
#include "Window.hpp"
#include <vector>

namespace crgwin {

	class Window;

	class Platform {
	protected:
		static std::vector<Window*> windows;
	public:
		virtual unsigned long long GetTimeCycles() = 0;

		void Tick() = delete;

		static void RegisterWindow(Window* window);
		static void UnregisterWindow(Window* window);
		static Window* GetByHandle(WindowHandle handle);
	};
}