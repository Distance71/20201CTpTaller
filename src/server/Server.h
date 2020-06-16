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
#include "../common/transmitionManager/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"

class ServerTransmitionManager;

class Server {
    private:
        ServerTransmitionManager *transmitionManager_;

        size_t port_;
        size_t maxPlayers;
        unordered_map<IdPlayer, UsersManager*> players_;
        bool connected_;

        void initializeServer();
        
    public:
        Server(size_t port);
        ~Server();

        bool isConnected();
        bool waitPlayers();
        bool addPlayer(IdPlayer idPlayer, UsersManager *onePlayer);
        bool isFull();
        int run();
};

#endif