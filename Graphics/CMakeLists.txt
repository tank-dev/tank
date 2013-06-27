FILE(GLOB gfx_src *.cpp *.hpp)

add_subdirectory(GL)
set(gfx_src ${gfx_src} ${gl_src} PARENT_SCOPE)
