#!/usr/bin/env python
from __future__ import print_function
import os
import sys
import subprocess
import platform
import distutils.spawn

if sys.version_info[0] >= 3:
    get_input = input
else:
    get_input = raw_input

def main():
    project_name = get_input("What is the name of your game?\n")
    make_directories(project_name)
    install_dependencies()
    initialize_project(project_name)
    install_tank()

def make_directories(project_name):
    try:
        os.makedirs(project_name)
    except:
        print("Folder",project_name,"already exists!")
        exit(1)
    os.chdir(project_name)

    os.makedirs("src")
    os.makedirs("assets")
    os.makedirs("build")

no_deps_supported = "Sorry, you're on your own. You will need to install git,"\
        " SFML2 and Boost, if you haven't already. You should also set the"\
        " environment variables SFML_ROOT and BOOST_ROOT to the paths where you"\
        " installed them. Good Luck!"

def install_dependencies():
    print("Installing dependencies:")
    if sys.platform == "win32":
        print(no_deps_supported)
    if sys.platform == "darwin":
        print(no_deps_supported)
    if sys.platform == "linux":
        install_linux_dependencies()
    else:
        print("Unrecognized OS. Tank has not been tested on your OS, but will"
               " likely still work. You will need Boost and SFML2 installed."
               " If Tank works/doesn't work on your platform, please report it"
               " to us at https://github.com/Gazok/Tank so we can improve it!")

def install_linux_dependencies():
    distro,_,_ = platform.linux_distribution()
    if distro == "arch":
        subprocess.call(["sudo","pacman","-S","--needed","sfml","boost","git"])
    elif distro == "debian":
        subprocess.call(["sudo","apt-get","install","sfml-dev",
            "libboost-all-dev","git"])
    elif distro == "fedora":
        subprocess.call(["sudo","yum","install","sfml-devel","boost-devel",
            "git"])
    else:
        print(no_deps_supported)

def install_tank():
    if not distutils.spawn.find_executable("git"):
        print("To get Tank, you need to install git first."
                " If you have it installed, make sure it is in your PATH!")
        exit(1)
    subprocess.call(["git","clone","https://github.com/Gazok/Tank"], 
            stdout=open(os.devnull, 'wb'))

def initialize_project(project_name):
    global cmake_template

    cmake_template = cmake_template.replace("<project_name>", project_name)

    root = open("CMakeLists.txt", "w")
    src = open("src/CMakeLists.txt", "w")
    main = open("src/main.cpp", "w")
    main_world_hpp = open("src/MainWorld.hpp", "w")
    main_world_cpp = open("src/MainWorld.cpp", "w")
    gitignore = open(".gitignore", "w")

    try:
        root.write(cmake_template)
        src.write(src_template)
        main.write(open_window)
        main_world_hpp.write(main_world_template_hpp)
        main_world_cpp.write(main_world_template_cpp)
        gitignore.write("build/\n")
    finally:
        root.close()
        src.close()

############ FILE TEMPLATES.... HERE BE DRAGONS! ##############
cmake_template = r"""CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project (<project_name>)

add_subdirectory(Tank)

include_directories(${TANK_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Za /W0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-mismatched-tags")
endif()

add_subdirectory(src)
file(COPY "assets" DESTINATION ${CMAKE_BINARY_DIR})
"""

src_template = """file(GLOB sources *.cpp)
file(GLOB headers *.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${CMAKE_PROJECT_NAME} tank)
"""

open_window = """#include <Tank/System/Game.hpp>
#include "MainWorld.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::makeWorld<MainWorld>();
    tank::Game::run();
}
"""

main_world_template_hpp = """#include <Tank/System/World.hpp>

class MainWorld : public tank::World
{
public:
    MainWorld();
};
"""

main_world_template_cpp = """#include "MainWorld.hpp"

MainWorld::MainWorld()
{
}
"""
main()
