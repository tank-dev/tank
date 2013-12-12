FILE(GLOB gfx_src *.cpp *.hpp)
#add_library(tank_graphics ${gfx_src})
set(gfx_src ${gfx_src} PARENT_SCOPE)
