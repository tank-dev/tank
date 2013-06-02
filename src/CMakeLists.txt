add_subdirectory(System)
add_subdirectory(Utility)
add_subdirectory(Graphics)

add_library(engine ${engine_sources})

find_package(SDL REQUIRED) 
find_package(SDL_image REQUIRED) 
find_package(SDL_mixer REQUIRED) 

if(SDL_FOUND)
    include_directories(${SDL_INCLUDE_DIRS})
    target_link_libraries(engine ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY})
endif(SDL_FOUND) 
