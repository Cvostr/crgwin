#pragma once

namespace crgwin {
	class Mutex {
	protected:
		void* _handle;
	public:

		Mutex();

		~Mutex();

		void Lock();

		void Unlock();

		void Destroy();
	};
}