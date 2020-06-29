#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <errno.h>

#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/messages/MessageActionPlayer.h"
#include "../../common/models/messages/MessageInitEntity.h"
#include "../../common/models/messages/MessageInitLayer.h"
#include "../../common/models/messages/MessageInitScreen.h"
#include "../../common/models/messages/MessageMovementPlayer.h"
#include "../../common/models/messages/MessageUpdateEntity.h"
#include "../../common/models/messages/MessageUpdateStage.h"
#include "../../common/models/BlockingQueue.h"
#include "../../common/services/ThreadsHandler.h"

#include "../Server.h"
#include "../models/User.h"


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
};

#endif // _SERVER_TRANSMITION_MANAGER_H_
