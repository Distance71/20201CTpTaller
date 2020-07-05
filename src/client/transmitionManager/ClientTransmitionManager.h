#ifndef _CLIENT_TRANSMITION_MANAGER_H_
#define _CLIENT_TRANSMITION_MANAGER_H_


#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include "../Client.h"
#include "../../common/models/Socket.h"
#include "../../common/services/serializer/MessageDeserializer.h"
#include "../../common/models/messages/Message.h"

class MessageDeserializer;

class ClientTransmitionManager {

    private:
        Client* client_;
        Socket* socket_;
        MessageDeserializer *deserializer_;
        vector<Message*>* sendMessagesQueue_;

    public:
    
        ClientTransmitionManager(Client *client, size_t port);
        ~ClientTransmitionManager();
        void sendMessage(Message* message);
        bool connectWithServer(string ipAddress);
        Client *getClient();
        Socket *getSocket();
        MessageDeserializer *getDeserializer();
        vector<Message *> *getSendMessagesQueue();
        void run();
};
#endif 