#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

#include "transmitionManager/ServerTransmitionManager.h"
#include "usersManager/UsersManager.h"

#include "../common/types.h"
#include "../common/models/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"
#include "eventsManager/ServerEventsManager.h"

#include "models/Game.h"

class ServerTransmitionManager;
class ServerEventsManager;
class UsersManager;

class Server {
    private:
        size_t port_;
        Socket *socket_;
        UsersManager* usersManager_;
        ServerTransmitionManager* transmitionManager_;
        ServerEventsManager* eventsManager_;
        bool connected_ = false;
        bool gameRunning_ = false;
        
        pthread_mutex_t mutex_players_;

        void _initializeServer();
        
    public:
        Server(size_t port);
        ~Server();

        bool isConnected();
        void waitPlayers();
        void addPlayer(User *newUser);
        bool isFull();
        int run();
        void runGame();
        
        Socket* getSocket();
        BlockingQueue<Message *>* getEventsToProcess();
};

#endif