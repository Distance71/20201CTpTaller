#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

#include "usersManager/UsersManager.h"
#include "../common/types.h"
#include "../common/models/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"
#include "eventsManager/ServerEventsManager.h"
#include "../common/models/events/Event.h"

#include "../common/models/events/EventInitStage.h"
#include "models/Game.h"

class ServerEventsManager;
class UsersManager;
class Game;

class Server {
    private:
        size_t port_;
        Socket *socket_;
        Game *game;
        UsersManager* usersManager_;
        ServerEventsManager* eventsManager_;
        bool connected_ = false;
        bool gameRunning_ = false;
        
        pthread_mutex_t mutex_players_;
        
        void _initializeServer();
        
    public:
        Server(size_t port);
        ~Server();
        int run();

        
        void processEvent(Event *event);
        
        bool isConnected();
       
        void runGame();
        
        
        Socket* getSocket();
        void sendToAllUsers(Event* event);

        void moveUser(Id idUser, orientation_t orientation);
};

#endif