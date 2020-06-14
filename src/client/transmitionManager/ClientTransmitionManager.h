#ifndef _CLIENT_TRANSMITION_MANAGER_H_
#define _CLIENT_TRANSMITION_MANAGER_H_


#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../Client.h"
#include "../../common/transmitionManager/Socket.h"

class Client;

class ClientTransmitionManager {

    private:
        Client *clientOwn_;
        Socket *socket_;

    public:
        ClientTransmitionManager(Client *client, size_t port);
        ~ClientTransmitionManager();
    
        bool connectWithServer(string ipAddress);
};

#endif // _CLIENT_TRANSMITION_MANAGER_H_