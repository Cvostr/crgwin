#include <platforms/PlatformKeyMap.hpp>

crgwin::PlatformKeyMappings::PlatformKeyMappings() {

}
crgwin::PlatformKeyMappings::~PlatformKeyMappings() {

}

void crgwin::PlatformKeyMappings::AddKeyMapping(int platform_code, crgKeyCode uni_code) {
	if (mappings_vec.size() <= platform_code) {
		mappings_vec.resize(platform_code + 1);
	}
	mappings_vec[platform_code] = uni_code;
}

crgKeyCode crgwin::PlatformKeyMappings::GetKeyMapping(int platform_code) {
	if (mappings_vec.size() <= platform_code)
		return (crgKeyCode)0;
	return mappings_vec[platform_code];
}

void crgwin::PlatformKeyMappings::AddKeyMappings(KeyMappingPair* mappings, int size) {
	int max_code = 0;
	for (int i = 0; i < size; i++) {
		KeyMappingPair* pair = &mappings[i];
		if (pair->platform_code > max_code)
			max_code = pair->platform_code;
	}

	mappings_vec.resize(max_code + 1);

	for (int i = 0; i < size; i++) {
		KeyMappingPair* pair = &mappings[i];
		mappings_vec[pair->platform_code] = pair->crg_code;
	}
}