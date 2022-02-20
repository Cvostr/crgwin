#pragma once

namespace crgwin {
	class CpuInfo {
	public:
		unsigned int CpuCoreCount;

		unsigned int CpuLogicalCoreCount;

		unsigned int L1CacheSize;

		unsigned int L2CacheSize;

		unsigned int L3CacheSize;

		unsigned int CpuFrequency;
	};
}