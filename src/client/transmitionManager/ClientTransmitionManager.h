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
#include "../../common/transmitionManager/Socket.h"
#include "../../common/transmitionManager/serializer/MessageDeserializer.h"
#include "../../common/messages/Message.h"
#include "../../common/messages/MessageActionPlayer.h"
#include "../../common/messages/MessageInitEntity.h"
#include "../../common/messages/MessageInitLayer.h"
#include "../../common/messages/MessageInitScreen.h"
#include "../../common/messages/MessageMovementPlayer.h"
#include "../../common/messages/MessageUpdateEntity.h"
#include "../../common/messages/MessageUpdateStage.h"

class Client;

class ClientTransmitionManager {

    private:
        Client *clientOwn_;
        Socket *socket_;

        vector<Message *> queueReceiveMessage_;
        vector<Message *> queueSendMessage_;
        MessageDeserializer *deserializer_;

    public:
        ClientTransmitionManager(Client *client, size_t port);
        ~ClientTransmitionManager();
    
        bool connectWithServer(string ipAddress);

        Client *getClient();
        Socket *getSocket();
        vector<Message *> *getReceivedMessages();
        vector<Message *> *getSendMessages();
        MessageDeserializer *getDeserializer();
};

#endif // _CLIENT_TRANSMITION_MANAGER_H_