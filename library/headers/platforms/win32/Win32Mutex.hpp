#pragma once

#include <base/Mutex.hpp>

namespace crgwin {
	class Win32Mutex : public crgwin::Mutex {
	public:
		Win32Mutex();

		~Win32Mutex();

		void Lock();

		void Unlock();

		void Destroy();
	};
}