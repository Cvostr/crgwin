#pragma once

namespace crgwin {
	class Mutex {
	protected:
		void* _handle;
	public:

		Mutex() {

		}

		virtual ~Mutex() {

		}

		virtual void Lock() = 0;

		virtual void Unlock() = 0;

		virtual void Destroy() = 0;
	};
}