FILE(GLOB audio_src *.cpp *.hpp)
add_library(tank_audio OBJECT ${audio_src})
