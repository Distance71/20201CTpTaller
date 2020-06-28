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
#include "../../common/models/messages/MessageActionPlayer.h"
#include "../../common/models/messages/MessageInitEntity.h"
#include "../../common/models/messages/MessageInitLayer.h"
#include "../../common/models/messages/MessageInitScreen.h"
#include "../../common/models/messages/MessageMovementPlayer.h"
#include "../../common/models/messages/MessageUpdateEntity.h"
#include "../../common/models/messages/MessageUpdateStage.h"

class Client;

class ClientTransmitionManager {

    private:
        Client *clientOwn_;
        Socket *socket_;

        vector<Message *> queueReceiveMessage_;
        vector<Message *> queueSendMessage_;
        MessageDeserializer *deserializer_;

        void processInitEntity(MessageInitEntity *initEntity);
        void processInitLayer(MessageInitLayer *initLayer);
        void processInitScreen(MessageInitScreen *initScreen);
        void processRequestLoginPlayer(MessageRequestLoginPlayer *requestLogin);
        void processUpdateEntity(MessageUpdateEntity *updateEntity);
        void processUpdateStage(MessageUpdateStage *updateStage);

    public:
        ClientTransmitionManager(Client *client, size_t port);
        ~ClientTransmitionManager();
    
        bool connectWithServer(string ipAddress);

        Client *getClient();
        Socket *getSocket();
        vector<Message *> *getReceivedMessages();
        vector<Message *> *getSendMessages();
        MessageDeserializer *getDeserializer();
        void processMessages();

        void sendMovement(orientation_t moveOrientation);
};

#endif // _CLIENT_TRANSMITION_MANAGER_H_