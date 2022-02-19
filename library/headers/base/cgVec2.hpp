#pragma once

namespace crgwin {
	class ivec2 {
	public:
		int x;
		int y;

		ivec2() : x(0), y(0) {}
		ivec2(int x, int y) : x(x), y(y) {}
	};
}