#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include "../common/transmitionManager/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"

class Server {
    private:
        Socket *socket_;
        size_t port_;
        size_t maxPlayers;
        vector<int> players;
        bool connected_;

        void initializeServer();
        
    public:
        Server(size_t port);
        ~Server();

        bool isConnected();
        bool waitPlayers();
        int run();
};

#endif