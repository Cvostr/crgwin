#pragma once

namespace crgwin {

	enum class BatteryState {
		STATE_UNKNOWN,
		STATE_CHARGING,
		STATE_DISCHARGIND
	};

	class BatteryInfo {
	public:
		BatteryState state;
		float battery_charge;

		BatteryInfo() : state(STATE_UNKNOWN), battery_charge(0) {}
	};
}