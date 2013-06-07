find_package(SDL REQUIRED) 
find_package(SDL_image REQUIRED) 
find_package(SDL_mixer REQUIRED) 
include_directories(${SDL_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT MSVC)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif (APPLE)

set(CMAKE_BUILD_TYPE Debug)

option(Warn "Compile using all warnings" ON)

if(Warn)
    if (NOT MSVC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX")
    endif(NOT MSVC)
endif(Warn)

add_subdirectory(System)
add_subdirectory(Utility)
add_subdirectory(Graphics)

set (engine_src ${gfx_src} ${sys_src} ${util_src})
add_library(engine ${engine_src})
target_link_libraries(engine ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
