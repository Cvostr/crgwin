#pragma once

#include <string>

typedef const wchar_t* LPCWSTR;

namespace crgwin {
	LPCWSTR CStrToWSTR(const std::string& str);
}