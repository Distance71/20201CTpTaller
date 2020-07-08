#ifndef _CLIENT_TRANSMITION_MANAGER_H_
#define _CLIENT_TRANSMITION_MANAGER_H_


#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../Client.h"
#include "../../common/models/Socket.h"
#include "../../common/services/serializer/MessageDeserializer.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/BlockingQueue.h"

class Client;

class ClientTransmitionManager {

    private:
        Client* clientOwn_;
        Socket* socket_;
        BlockingQueue<Message*>* sendMessagesQueue_;



    public:
        ClientTransmitionManager(Client *client);
        ~ClientTransmitionManager();
        void runThreads();
        bool connectWithServer();
        void sendMessage(Message* message);   
};
#endif 