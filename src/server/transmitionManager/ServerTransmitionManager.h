#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include "../../common/transmitionManager/Socket.h"
#include "../Server.h"

class Server;

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        Socket *socket_;
        size_t maxPlayers;
        vector<int> players;

    public:
        ServerTransmitionManager(Server *server, size_t port);
        ~ServerTransmitionManager();

        bool initialize();
        bool waitPlayers();
};

#endif