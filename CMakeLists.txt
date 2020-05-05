cmake_minimum_required(VERSION 3.10)
project(tp1taller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/vendor/")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(src/game)
include_directories(src/providers)
include_directories(src/services)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable( tp1taller
        src/game/models/Game.cpp
        src/game/models/Game.h
        src/game/models/Map.cpp
        src/game/models/Map.h
        src/game/models/MapElement.cpp
        src/game/models/MapElement.h
        src/game/models/Orientation.cpp
        src/game/models/Orientation.h
        src/game/models/Position.cpp
        src/game/models/Position.h
	src/game/models/MovementHandler.h
	src/game/models/MovementHandler.cpp
	src/game/models/PlayerController.cpp
	src/game/models/PlayerController.h
	src/game/models/Action.cpp
	src/game/models/Action.h
	src/game/models/State.cpp
	src/game/models/State.h
	src/game/models/Sprite.cpp
	src/game/models/Sprite.h
	src/game/models/Speed.cpp
	src/game/models/Speed.h
        src/game/graphics/Graphics.cpp
        src/game/graphics/Graphics.h
        src/game/graphics/GraphicsScenario.cpp
        src/game/graphics/GraphicsScenario.h
        src/game/graphics/GraphicsSpacecraft.cpp
        src/game/graphics/GraphicsSpacecraft.h
        src/game/main.cpp
        src/providers/GameProvider.cpp
        src/providers/GameProvider.h
        src/services/ConfigurationHandler.cpp
        src/services/ConfigurationHandler.h
        src/services/Logger.cpp
        src/services/Logger.h
        src/services/ParserJson.cpp
        src/services/ParserJson.h)
	
target_link_libraries(tp1taller ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
