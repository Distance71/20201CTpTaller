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
#include "../../common/services/serializer/MessageSerializer.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/BlockingQueue.h"
#include "../../common/models/messages/MessageEndGame.h"

class Client;
class MessageDeserializer;
class MessageSerializer;

class ClientTransmitionManager {

    private:
        Client* client_;
        Socket* socket_;
        MessageDeserializer *deserializer_;
        MessageSerializer *serializer_;
        BlockingQueue<Message*>* sendMessagesQueue_;

    public:
         ClientTransmitionManager(Client *client, size_t port);
        ~ClientTransmitionManager();

        void sendSerializedMessage(Message* message);
        void sendMessage(Message* message);
        bool connectWithServer(string ipAddress);
        Client *getClient();
        Socket *getSocket();
        MessageDeserializer *getDeserializer();
        BlockingQueue<Message*> *getSendMessagesQueue();
        void run();
};
#endif 