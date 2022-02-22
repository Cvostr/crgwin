#include <platforms/win32/Win32Mutex.hpp>

#ifdef _WIN32
#include <windows.h>

crgwin::Win32Mutex::Win32Mutex() {
	_handle = new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)_handle);
}

crgwin::Win32Mutex::~Win32Mutex() {
	Destroy();
}

void crgwin::Win32Mutex::Lock() {
	EnterCriticalSection((CRITICAL_SECTION*)_handle);
}

void crgwin::Win32Mutex::Unlock() {
	LeaveCriticalSection((CRITICAL_SECTION*)_handle);
}

void crgwin::Win32Mutex::Destroy() {
	if (_handle) {
		DeleteCriticalSection((CRITICAL_SECTION*)_handle);
		_handle = nullptr;
	}
}

#endif