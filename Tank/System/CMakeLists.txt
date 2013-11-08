FILE(GLOB sys_src *.cpp *.hpp)
add_library(tank_system ${sys_src})
set(sys_src ${sys_src} PARENT_SCOPE)