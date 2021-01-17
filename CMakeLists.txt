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
SET( turbohiker_src Source/turbohiker/Entity.cpp Source/turbohiker/Utils.cpp Source/turbohiker/World.cpp Source/turbohiker/EntityFactory.h Source/turbohiker/Player.cpp Source/turbohiker/Background.cpp Source/turbohiker/PassingHiker1.cpp Source/turbohiker/Random.cpp  Source/turbohiker/PassingHiker2.cpp Source/turbohiker/RacingHiker.cpp Source/turbohiker/RacingHiker.h Source/turbohiker/ScoreObserver.cpp Source/turbohiker/ScoreObserver.h Source/turbohiker/ScoreSubject.cpp Source/turbohiker/ScoreSubject.h)

ADD_LIBRARY( turbohiker STATIC ${turbohiker_src} )
#

SET( src Source/Game.cpp Source/presentation/Transformation.cpp Source/presentation/Factory.cpp Source/presentation/Player.cpp Source/presentation/Background.cpp Source/presentation/PassingHiker1.cpp Source/presentation/PassingHiker2.cpp  Source/presentation/Animation.cpp Source/presentation/RacingHiker.cpp Source/presentation/RacingHiker.h Source/presentation/Scoreboard.cpp Source/presentation/Scoreboard.h)
add_executable(TurboHiker main.cpp ${src})

target_link_libraries (TurboHiker turbohiker sfml-graphics sfml-window sfml-system sfml-audio)