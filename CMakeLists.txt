cmake_minimum_required(VERSION 2.8)
project (Tank)

#Old SDL stuff
find_package(SDL REQUIRED) 
find_package(SDL_image REQUIRED) 
find_package(SDL_mixer REQUIRED) 
include_directories(${SDL_INCLUDE_DIRS})

#New SFML/OpenGL stuff
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/modules/)
find_package(SFML 2.0 REQUIRED system window graphics)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${ImageMagick_INCLUDE_DIRS})

#This is the wrong way to do this, just temporary
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT MSVC)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif (APPLE)

set(CMAKE_BUILD_TYPE Debug)

option(Warn "Compile using all warnings" ON)
option(Debug "Compile using all warnings" ON)

if(Warn)
    if (NOT MSVC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX")
    endif(NOT MSVC)
endif(Warn)

if(Debug)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif(Debug)

add_subdirectory(System)
add_subdirectory(Utility)
add_subdirectory(Graphics)

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

set (engine_src ${gfx_src} ${sys_src} ${util_src})
add_library(engine ${engine_src})
target_link_libraries(engine ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${GLEW_LIBRARY} ${ImageMagick_LIBRARY})
if(Cotire)
    cotire(engine)
endif(Cotire)
