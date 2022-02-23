#include <base/Mutex.hpp>

#ifdef _WIN32
#include <windows.h>

crgwin::Mutex::Mutex() {
	_handle = new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)_handle);
}

crgwin::Mutex::~Mutex() {
	Destroy();
}

void crgwin::Mutex::Lock() {
	EnterCriticalSection((CRITICAL_SECTION*)_handle);
}

void crgwin::Mutex::Unlock() {
	LeaveCriticalSection((CRITICAL_SECTION*)_handle);
}

void crgwin::Mutex::Destroy() {
	if (_handle) {
		DeleteCriticalSection((CRITICAL_SECTION*)_handle);
		_handle = nullptr;
	}
}

#endif