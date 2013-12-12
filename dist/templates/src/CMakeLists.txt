file(GLOB sources *.cpp)
file(GLOB headers *.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${CMAKE_PROJECT_NAME} tank)
