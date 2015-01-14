cmake_minimum_required(VERSION 2.8.11)
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
set(TANK_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

if (${PROJECT_NAME} STREQUAL "Tank")
    set(TANK_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
    include_directories(${TANK_INCLUDE_DIRS})
else()
    set(TANK_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR} 
        ${Boost_INCLUDE_DIR} PARENT_SCOPE)
endif()

include_directories(${TANK_INCLUDE_DIRS})

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

option(WARN "Compile using all warnings" ON)

if(WARN)
    if (NOT MSVC)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-mismatched-tags")
    endif(NOT MSVC)
endif(WARN)

add_subdirectory(Tank/Audio)
add_subdirectory(Tank/Graphics)
add_subdirectory(Tank/System)
add_subdirectory(Tank/Utility)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.css.in
      ${CMAKE_CURRENT_BINARY_DIR}/doxygen.css)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/header.html.in
      ${CMAKE_CURRENT_BINARY_DIR}/header.html)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/footer.html.in
      ${CMAKE_CURRENT_BINARY_DIR}/footer.html)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/bootstrap3
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html/bootstrap3
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/jquery-2.1.3.min.js
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxy-boot.js
            ${CMAKE_CURRENT_BINARY_DIR}/doc/html
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_library(tank ${audio_src} ${gfx_src} ${sys_src} ${util_src})
target_link_libraries(tank ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
