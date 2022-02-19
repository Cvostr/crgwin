#include <platforms/win32/Win32Utils.hpp>
#ifdef _WIN32
#include <windows.h>


LPCWSTR crgwin::CStrToWSTR(const std::string& str) {
	wchar_t* result_str = new WCHAR[str.size() + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, result_str, 256);
	return result_str;
}

#endif