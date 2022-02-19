cmake_minimum_required (VERSION 3.14)

project ("crgwin")

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES   src/platforms/win32/Win32Window.cpp
				src/platforms/win32/Win32Utils.cpp
				src/platforms/win32/Win32Platform.cpp
				src/Window.cpp)

set(HEADER 	headers/base/Platform.hpp 
			headers/base/Window.hpp
			headers/platforms/win32/Win32Window.hpp
			headers/platforms/win32/Win32Utils.hpp
			headers/platforms/win32/Win32Platform.hpp)

include_directories("./headers" REQUIRED)

add_library (crgwin ${SRC_FILES} ${HEADER_FILES})