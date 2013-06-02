add_subdirectory(System)
add_subdirectory(Utility)
add_subdirectory(Graphics)

set (engine_src ${gfx_src} ${sys_src} ${util_src})
add_library(engine ${engine_src})
target_link_libraries(engine ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
