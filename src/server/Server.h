#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../common/transmitionManager/Socket.h"
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"

class Server {
    private:
        Socket *socket_;
        bool connected_;

        void initializeServer();
        
    public:
        Server(size_t port);
        ~Server();

        bool isConnected();
        int run();
};

#endif