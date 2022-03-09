#pragma once

#include <base/InputConstants.hpp>
#include <vector>

namespace crgwin {

	struct KeyMappingPair {
		int platform_code;
		crgKeyCode crg_code;
	};

	class PlatformKeyMappings {
	private:
		std::vector<crgKeyCode> mappings_vec;
	public:
		PlatformKeyMappings();
		~PlatformKeyMappings();

		void AddKeyMapping(int platform_code, crgKeyCode uni_code);

		void AddKeyMappings(KeyMappingPair* mappings, int size);

		crgKeyCode GetKeyMapping(int platform_code);

	};
}