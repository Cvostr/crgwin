cmake_minimum_required (VERSION 3.14)

project ("crgwin")

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS} -g")

set(SRC_FILES   
				src/crgwin.cpp
				src/platforms/win32/Win32Window.cpp
				src/platforms/win32/Win32Utils.cpp
				src/platforms/win32/Win32Platform.cpp
				src/platforms/win32/Win32Input.cpp
				src/platforms/win32/Win32Mutex.cpp
				src/platforms/win32/Win32DialogBox.cpp

				src/platforms/linux/LinuxWindow.cpp
				src/platforms/linux/LinuxPlatform.cpp
				src/platforms/linux/LinuxInput.cpp
				src/platforms/linux/LinuxMutex.cpp
				src/platforms/linux/LinuxAtoms.cpp
				src/platforms/linux/LinuxDialogBox.cpp

				src/platforms/PlatformKeyMap.cpp
				src/base/Window.cpp
				src/base/Platform.cpp)

set(HEADER 	
			headers/crgwin.hpp
			headers/base/Platform.hpp 
			headers/base/Window.hpp
			headers/base/BatteryInfo.hpp
			headers/base/CpuInfo.hpp
			headers/base/MemoryInfo.hpp
			headers/base/DialogBox.hpp
			headers/base/Mutex.hpp

			headers/platforms/win32/Win32Window.hpp
			headers/platforms/win32/Win32Utils.hpp
			headers/platforms/win32/Win32Platform.hpp
			
			headers/platforms/linux/LinuxAtoms.hpp
			headers/platforms/linux/LinuxWindow.hpp
			headers/platforms/linux/LinuxPlatform.hpp)

include_directories("./headers" REQUIRED)

add_library (crgwin ${SRC_FILES} ${HEADER_FILES})


IF(UNIX)
target_link_libraries(crgwin X11)
target_link_libraries(crgwin ${CMAKE_DL_LIBS})
target_link_libraries(crgwin pthread)
target_link_libraries(crgwin ${GTK_LIBRARIES})

ENDIF()
