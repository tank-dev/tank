CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(Tank)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif(NOT MSVC)

set(CMAKE_BUILD_TYPE Debug)

if(NOT MSVC)
    option(Warn "Compile using all warnings" ON)
endif(NOT MSVC)

if(Warn)
    set (CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")
endif(Warn)

add_subdirectory(src)
