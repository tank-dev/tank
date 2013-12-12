cmake_minimum_required(VERSION 2.8.9)
if (NOT DEFINED PROJECT_NAME)
    project (Tank)
endif()

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(SFML 2.0 REQUIRED system window graphics audio)
find_package(Threads REQUIRED)
find_package(Boost 1.53.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (${PROJECT_NAME} STREQUAL "Tank")
    set(TANK_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
    include_directories(${TANK_INCLUDE_DIRS})
    option(TESTS "Build unit tests" ON)
else()
    set(TANK_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIR} PARENT_SCOPE)
endif()

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT MSVC)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za")
endif()

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
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-mismatched-tags")
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-mismatched-tags")
        endif()
    endif(NOT MSVC)
endif(WARN)

set(COMPILE_DEFINITIONS_DEBUG "${COMPILE_DEFINITIONS_DEBUG} -DDEBUG")

add_subdirectory(deps)

add_subdirectory(Tank/Audio)
add_subdirectory(Tank/Graphics)
add_subdirectory(Tank/System)
add_subdirectory(Tank/Utility)

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

#add_library(tank_static ${audio_src} ${gfx_src} ${sys_src} ${util_src})
#target_link_libraries(tank_static ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_library(tank SHARED ${audio_src} ${gfx_src} ${sys_src} ${util_src})
target_link_libraries(tank ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

if(TESTS)
    add_subdirectory(tests)
endif()

