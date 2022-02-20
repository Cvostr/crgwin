#pragma once

namespace crgwin {
	class MemoryStats {
	public:
		unsigned long long TotalPhysicalMemory;

		unsigned long long UsedPhysicalMemory;

		unsigned long long TotalVirtualMemory;

		unsigned long long UsedVirtualMemory;

		unsigned long long ProcessUsedPhysicalMemory;

		unsigned long long ProcessUsedVirtualMemory;
	};
}