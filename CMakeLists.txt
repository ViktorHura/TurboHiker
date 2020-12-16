cmake_minimum_required(VERSION 3.15)
project(TurboHiker)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "Lib/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "Lib/SFML-2.5.1/lib")
set(SFML_DIR "Lib/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(TurboHiker main.cpp)
target_link_libraries (TurboHiker sfml-graphics sfml-window sfml-system)