# This is the minimum version that supports the Qt5 methods we are using in
# cmake
cmake_minimum_required(VERSION 2.8.9)
project (Tank)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(SFML 2.0 REQUIRED system window graphics)
find_package(Threads REQUIRED)
find_package(Boost 1.53.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT MSVC)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -stdlib=libc++")
endif (APPLE)

if (${CMAKE_GENERATOR} MATCHES "Xcode")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

option(WARN "Compile using all warnings" ON)

if(WARN)
    if (NOT MSVC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX")
    endif(NOT MSVC)
endif(WARN)

set(COMPILE_DEFINITIONS_DEBUG "${COMPILE_DEFINITIONS_DEBUG} -DDEBUG")

add_subdirectory(System)
add_subdirectory(Utility)
add_subdirectory(Graphics)
add_subdirectory(Audio)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation" VERBATIM
    )
endif(DOXYGEN_FOUND)

set (engine_src ${gfx_src} ${sys_src} ${util_src} ${audio_src})
add_library(tank ${engine_src})
target_link_libraries(tank ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

if(Cotire)
    cotire(engine)
endif(Cotire)
