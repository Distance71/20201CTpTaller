cmake_minimum_required(VERSION 3.10)
project(tp1taller)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/vendor/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(Threads REQUIRED)  

set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(
                ${SDL2_INCLUDE_DIRS} 
                ${SDL2_IMAGE_INCLUDE_DIRS}
                ${SDL2_TTF_INCLUDE_DIR})

include_directories(src/common)
include_directories(src/client)
include_directories(src/server)

file(COPY src/client/assets DESTINATION ${CMAKE_BINARY_DIR})


add_executable(tp1taller        
        
        src/client/ClientTest.cpp
        src/client/ClientTest.h
        src/client/Client.cpp
        src/client/Client.h
        src/client/transmitionManager/ClientTransmitionManager.cpp
        src/client/transmitionManager/ClientTransmitionManager.h
        src/client/eventsManager/ClientEventsManager.cpp
        src/client/eventsManager/ClientEventsManager.h
        src/client/screenManager/graphics/GraphicsScenario.cpp
        src/client/screenManager/graphics/GraphicsScenario.h
        src/client/screenManager/graphics/GraphicsMapElement.cpp
        src/client/screenManager/graphics/GraphicsMapElement.h
        src/client/screenManager/graphics/GameGraphics.cpp
        src/client/screenManager/graphics/GameGraphics.h
        src/client/screenManager/ScreenManager.cpp
        src/client/screenManager/ScreenManager.h
        src/client/screenManager/loginMenu/Button.h
        src/client/screenManager/loginMenu/Button.cpp
        src/client/screenManager/loginMenu/Menu.h
        src/client/screenManager/loginMenu/Menu.cpp
        src/client/screenManager/loginMenu/TextBox.h
        src/client/screenManager/loginMenu/TextBox.cpp
        src/client/screenManager/loginMenu/MenuElement.h
        src/client/screenManager/loginMenu/MenuElement.cpp

        src/common/models/messages/Message.h
        src/common/models/messages/MessageGameInit.cpp
        src/common/models/messages/MessageGameInit.h
        src/common/models/messages/MessageRequestLoginPlayer.cpp
        src/common/models/messages/MessageRequestLoginPlayer.h
        src/common/models/messages/MessageUserMovement.cpp
        src/common/models/messages/MessageUserMovement.h
        src/common/models/messages/MessageResponseLoginPlayer.cpp
        src/common/models/messages/MessageResponseLoginPlayer.h
        src/common/models/messages/MessageAnimationInitStage.cpp
        src/common/models/messages/MessageAnimationInitStage.h
        src/common/models/messages/MessageInitStage.cpp
        src/common/models/messages/MessageInitStage.h
        src/common/models/messages/MessageMapElementCreate.cpp
        src/common/models/messages/MessageMapElementCreate.h
        src/common/models/messages/MessageMapElementUpdate.cpp
        src/common/models/messages/MessageMapElementUpdate.h
        src/common/models/messages/MessageMapElementDelete.cpp
        src/common/models/messages/MessageMapElementDelete.h
        src/common/models/messages/MessagePlayerDisconnect.cpp
        src/common/models/messages/MessagePlayerDisconnect.h
        src/common/models/messages/MessagePlayerReconnect.cpp
        src/common/models/messages/MessagePlayerReconnect.h
        src/common/models/messages/MessageEndStage.cpp
        src/common/models/messages/MessageEndStage.h
        src/common/models/messages/MessageEndGame.cpp
        src/common/models/messages/MessageEndGame.h
        src/common/models/messages/MessageLog.cpp
        src/common/models/messages/MessageLog.h

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
		src/common/models/BlockingQueue.h
		src/common/models/Semaphore.h
        src/common/models/Semaphore.cpp
        
        src/common/models/events/Event.h
        src/common/models/events/EventGameInit.cpp
        src/common/models/events/EventGameInit.h
        src/common/models/events/EventRequestLoginPlayer.cpp
        src/common/models/events/EventRequestLoginPlayer.h
        src/common/models/events/EventUserMovement.cpp
        src/common/models/events/EventUserMovement.h
        src/common/models/events/EventWriteLog.h
        src/common/models/events/EventWriteLog.cpp
        src/common/models/events/EventResponseLoginPlayer.h
        src/common/models/events/EventResponseLoginPlayer.cpp
        src/common/models/events/EventResponseLoginPlayer.h
        src/common/models/events/EventAnimationInitStage.cpp
        src/common/models/events/EventAnimationInitStage.h
        src/common/models/events/EventInitStage.cpp
        src/common/models/events/EventInitStage.h
        src/common/models/events/EventMapElementCreate.cpp
        src/common/models/events/EventMapElementCreate.h
        src/common/models/events/EventMapElementUpdate.cpp
        src/common/models/events/EventMapElementUpdate.h
        src/common/models/events/EventMapElementDelete.cpp
        src/common/models/events/EventMapElementDelete.h
        src/common/models/events/EventPlayerDisconnect.cpp
        src/common/models/events/EventPlayerDisconnect.h
        src/common/models/events/EventPlayerReconnect.cpp
        src/common/models/events/EventPlayerReconnect.h
        src/common/models/events/EventEndStage.cpp
        src/common/models/events/EventEndStage.h
        src/common/models/events/EventEndGame.cpp
        src/common/models/events/EventEndGame.h

        src/common/providers/GameProvider.cpp
        src/common/providers/GameProvider.h

        src/common/services/serializer/MessageDeserializer.cpp
        src/common/services/serializer/MessageDeserializer.h
        src/common/services/serializer/MessageSerializer.cpp
        src/common/services/serializer/MessageSerializer.h

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

        src/server/transmitionManager/ServerTransmitionManager.cpp
        src/server/transmitionManager/ServerTransmitionManager.h
        
        src/server/usersManager/UsersManager.cpp
        src/server/usersManager/UsersManager.h
        
        src/main.cpp)




target_link_libraries(tp1taller ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

