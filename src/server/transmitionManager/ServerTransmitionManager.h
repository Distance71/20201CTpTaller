#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <errno.h>

#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/messages/Message.h"
#include "../../common/messages/MessageActionPlayer.h"
#include "../../common/messages/MessageInitEntity.h"
#include "../../common/messages/MessageInitLayer.h"
#include "../../common/messages/MessageInitScreen.h"
#include "../../common/messages/MessageMovementPlayer.h"
#include "../../common/messages/MessageUpdateEntity.h"
#include "../../common/messages/MessageUpdateStage.h"
#include "../../common/models/BlockingQueue.h"

#include "../Server.h"

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        BlockingQueue* receivedMessagesQueue_;
        unordered_map<IdUser, BlockingQueue *> messagesQueues_;

        void createReceivingCycle(User* user);
        void* receivingCycle(User* user);

    public:
        ServerTransmitionManager(Server *server);
        ~ServerTransmitionManager();

        void addUser(User* user);
        BlockingQueue* getMessagesToProcess();
        //bool initialize();
        //bool waitPlayers();
};

#endif