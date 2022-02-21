#pragma once

#include "BatteryInfo.hpp"
#include "CpuInfo.hpp"
#include "MemoryInfo.hpp"

namespace crgwin {
	class Platform {
	public:
		virtual unsigned long long GetTimeCycles() = 0;

		void Tick() = delete;
	};
}