CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
project (<project_name>)

add_subdirectory(src)
file(COPY "assets" DESTINATION ${CMAKE_BINARY_DIR})
