cmake_minimum_required(VERSION 3.15)
project(TurboHiker)

set(CMAKE_CXX_STANDARD 14)

# SFML lib
set(SFML_INCLUDE_DIR "Lib/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "Lib/SFML-2.5.1/lib")
set(SFML_DIR "Lib/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
#

# Static game logic lib
SET( turbohiker_src Source/turbohiker/Entity.cpp Source/turbohiker/Utils.cpp Source/turbohiker/Utils.h)

ADD_LIBRARY( turbohiker STATIC ${turbohiker_src} )
#

SET( src Source/Game.cpp Source/presentation/Transformation.cpp)
add_executable(TurboHiker main.cpp ${src})

target_link_libraries (TurboHiker turbohiker sfml-graphics sfml-window sfml-system)