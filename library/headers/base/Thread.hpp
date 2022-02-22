#pragma once

namespace crgwin {
	class Thread {
	protected:
		void* _handle;
	public:
		Thread() {

		}

		virtual ~Thread() {

		}
	};
}