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
        src/client/eventsManager/ClientEventsManager.cpp
        src/client/eventsManager/ClientEventsManager.h

        src/client/graphics/GraphicsScenario.cpp
        src/client/graphics/GraphicsScenario.h
        src/client/graphics/GraphicsMapElement.cpp
        src/client/graphics/GraphicsMapElement.h
        src/client/graphics/GraphicsGeneral.cpp
        src/client/graphics/GraphicsGeneral.h

        src/client/transmitionManager/ClientTransmitionManager.cpp
        src/client/transmitionManager/ClientTransmitionManager.h

        src/client/Client.cpp
        src/client/Client.h
        src/client/GameScreen.cpp
        src/client/GameScreen.h

        src/client/loginMenu/Button.h
        src/client/loginMenu/Button.cpp
        src/client/loginMenu/Menu.h
        src/client/loginMenu/Menu.cpp
        src/client/loginMenu/TextBox.h
        src/client/loginMenu/TextBox.cpp
        src/client/loginMenu/MenuElement.h
        src/client/loginMenu/MenuElement.cpp

        src/common/models/messages/Message.h
        src/common/models/messages/MessageGameInit.cpp
        src/common/models/messages/MessageGameInit.h

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
        src/common/models/events/EventGameInit.h
        src/common/models/events/EventGameInit.cpp
        src/common/models/events/EventResponseLoginPlayer.h
        src/common/models/events/EventResponseLoginPlayer.cpp
        
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

