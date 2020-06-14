cmake_minimum_required(VERSION 3.10)
project(tp1taller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/vendor/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(src/common)
include_directories(src/providers)
include_directories(src/services)

add_executable( tp1taller
	src/common/models/Action.cpp
	src/common/models/Action.h        
	src/common/models/Game.cpp
        src/common/models/Game.h
        src/common/models/Map.cpp
        src/common/models/Map.h
        src/common/models/MapElement.cpp
        src/common/models/MapElement.h
	src/common/models/MovementHandler.h
	src/common/models/MovementHandler.cpp        
	src/common/models/Orientation.cpp
        src/common/models/Orientation.h
	src/common/models/PlayerController.cpp
	src/common/models/PlayerController.h
	src/common/models/EnemyIA.h
	src/common/models/EnemyIA.cpp
        src/common/models/Position.cpp
        src/common/models/Position.h
	src/common/models/Speed.cpp
	src/common/models/Speed.h
	src/common/models/Sprite.cpp
	src/common/models/Sprite.h
	src/common/models/State.cpp
	src/common/models/State.h
        src/client/graphicsManager/GraphicsScenario.cpp
        src/client/graphicsManager/GraphicsScenario.h
        src/client/graphicsManager/GraphicsMapElement.h
        src/client/graphicsManager/GraphicsMapElement.cpp
        src/main.cpp
	src/common/types.h
        src/common/providers/GameProvider.cpp
        src/common/providers/GameProvider.h
        src/common/services/ConfigurationHandler.cpp
        src/common/services/ConfigurationHandler.h
        src/common/services/Logger.cpp
        src/common/services/Logger.h
        src/common/services/ParserJson.cpp
        src/common/services/ParserJson.h


        src/common/transmitionManager/Socket.cpp
        src/common/transmitionManager/Socket.h
        src/client/transmitionManager/ClientTransmitionManager.cpp
        src/client/transmitionManager/ClientTransmitionManager.h
        src/client/GameScreen.cpp
        src/client/GameScreen.h
        src/client/Client.cpp
        src/client/Client.h
        src/server/Server.cpp
        src/server/Server.h)
	
target_link_libraries(tp1taller ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
