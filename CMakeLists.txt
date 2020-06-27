cmake_minimum_required(VERSION 3.10)
project(tp1taller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/vendor/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(
                ${SDL2_INCLUDE_DIRS} 
                ${SDL2_IMAGE_INCLUDE_DIRS}
                ${SDL2_TTF_INCLUDE_DIR})

include_directories(src/common)
include_directories(src/providers)
include_directories(src/services)

file(COPY src/client/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable( tp1taller
        src/client/clientModels/ClientMap.cpp
        src/client/clientModels/ClientMap.h
        src/client/clientModels/ClientMapElement.cpp
        src/client/clientModels/ClientMapElement.h
        
        src/client/controllers/ClientController.cpp
        src/client/controllers/ClientController.h
        
        src/client/eventsManager/ClientEventsManager.cpp
        src/client/eventsManager/ClientEventsManager.h

        src/client/graphicsManager/GraphicsScenario.cpp
        src/client/graphicsManager/GraphicsScenario.h
        src/client/graphicsManager/GraphicsMapElement.cpp
        src/client/graphicsManager/GraphicsMapElement.h

        src/client/transmitionManager/serializer/ClientDeserializer.cpp
        src/client/transmitionManager/serializer/ClientDeserializer.h
        src/client/transmitionManager/serializer/ClientSerializer.cpp
        src/client/transmitionManager/serializer/ClientSerializer.h
        src/client/transmitionManager/ClientTransmitionManager.cpp
        src/client/transmitionManager/ClientTransmitionManager.h

        src/client/Client.cpp
        src/client/Client.h
        src/client/GameScreen.cpp
        src/client/GameScreen.h

        src/common/messages/Message.cpp
        src/common/messages/Message.h
        src/common/messages/MessageActionPlayer.cpp
        src/common/messages/MessageActionPlayer.h
        src/common/messages/MessageInitEntity.cpp
        src/common/messages/MessageInitEntity.h
        src/common/messages/MessageInitLayer.cpp
        src/common/messages/MessageInitLayer.h
        src/common/messages/MessageInitScreen.cpp
        src/common/messages/MessageInitScreen.h
        src/common/messages/MessageLoginPlayer.cpp
        src/common/messages/MessageLoginPlayer.h
        src/common/messages/MessageMovementPlayer.cpp
        src/common/messages/MessageMovementPlayer.h
        src/common/messages/MessageRequestLoginPlayer.cpp
        src/common/messages/MessageRequestLoginPlayer.h
        src/common/messages/MessageUpdateEntity.cpp
        src/common/messages/MessageUpdateEntity.h
        src/common/messages/MessageUpdateStage.cpp
        src/common/messages/MessageUpdateStage.h

        src/common/models/Orientation.cpp
	src/common/models/Orientation.h
        src/common/models/Position.cpp
	src/common/models/Position.h
        src/common/models/Socket.cpp
	src/common/models/Socket.h
        src/common/models/Sprite.cpp
	src/common/models/Sprite.h
        src/common/models/State.cpp
	src/common/models/State.h

        src/common/providers/GameProvider.cpp
        src/common/providers/GameProvider.h

        src/common/serializer/MessageDeserializer.cpp
        src/common/serializer/MessageDeserializer.h
        src/common/serializer/MessageSerializer.cpp
        src/common/serializer/MessageSerializer.h

        src/common/services/ConfigurationHandler.cpp
        src/common/services/ConfigurationHandler.h
        src/common/services/Logger.cpp
        src/common/services/Logger.h
        src/common/services/ParserJson.cpp
        src/common/services/ParserJson.h
        src/common/services/ThreadsHandler.cpp
        src/common/services/ThreadsHandler.h

        src/common/types.h
        src/main.cpp
	
        src/server/eventsManager/ServerEventsManager.cpp
        src/server/eventsManager/ServerEventsManager.h

        src/common/models/Action.cpp
        src/common/models/Action.h
        src/server/models/EnemyIA.cpp
        src/server/models/EnemyIA.h
        src/server/models/Game.cpp
        src/server/models/Game.h
        src/server/models/Map.cpp
        src/server/models/Map.h
        src/server/models/MapElement.cpp
        src/server/models/MapElement.h
        src/server/models/MovementHandler.cpp
        src/server/models/MovementHandler.h
        src/server/models/PlayerController.cpp
        src/server/models/PlayerController.h
        src/server/models/Speed.cpp
        src/server/models/Speed.h
        src/server/models/User.cpp
        src/server/models/User.h
        
        src/server/Server.cpp
        src/server/Server.h

        src/server/transmitionManager/serializer/ServerSerializer.cpp
        src/server/transmitionManager/serializer/ServerSerializer.h
        src/server/transmitionManager/serializer/ServerDeserializer.cpp
        src/server/transmitionManager/serializer/ServerDeserializer.h

        src/server/transmitionManager/LogsManager.cpp
        src/server/transmitionManager/LogsManager.h
        src/server/transmitionManager/ServerTransmitionManager.cpp
        src/server/transmitionManager/ServerTransmitionManager.h
        
        src/server/usersManager/UsersManager.cpp
        src/server/usersManager/UsersManager.h
        
        src/main.cpp)
	
target_link_libraries(tp1taller ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
