#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <unordered_map>
#include "../../common/transmitionManager/Socket.h"
#include "../../common/types.h"
#include "../Server.h"

class Server;

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        Socket *socket_;
        size_t maxPlayers;
        
        unordered_map<IdPlayer, Socket*> players_;
        IdPlayer lastId_ = 0;

    public:
        ServerTransmitionManager(Server *server, size_t port);
        ~ServerTransmitionManager();

        bool initialize();
        bool waitPlayers();
};

#endif