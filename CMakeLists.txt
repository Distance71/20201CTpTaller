cmake_minimum_required(VERSION 3.16)
project(tp1taller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/vendor/")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(src/game)
include_directories(src/providers)
include_directories(src/services)

add_executable( tp1taller
        src/game/Game.cpp
        src/game/Game.h
        src/game/main.cpp
        src/providers/GameProvider.cpp
        src/providers/GameProvider.h
        src/services/ConfigurationHandler.cpp
        src/services/ConfigurationHandler.h
        src/services/Logger.cpp
        src/services/Logger.h
        Configuration.json)
target_link_libraries(tp1taller ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})