#ifndef _SERVER_H_
#define _SERVER_H_

#include <netinet/in.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../common/services/Logger.h"
#include "../common/providers/GameProvider.h"

class Server {
    private:
    int socket_;

    public:
    Server();
    ~Server();

    void initializeServer(size_t port);
    void run();
};

#endif