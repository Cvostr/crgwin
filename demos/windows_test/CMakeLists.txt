cmake_minimum_required (VERSION 3.14)

project ("windows_test")

set(CMAKE_CXX_STANDARD 17)

include_directories(../../library/headers REQUIRED)

set(SRC_FILES main.cpp)

add_executable (windows_test ${SRC_FILES})
target_link_libraries(windows_test crgwin)