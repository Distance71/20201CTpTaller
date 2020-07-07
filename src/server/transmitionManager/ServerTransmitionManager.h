#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <errno.h>

#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/BlockingQueue.h"
#include "../../common/services/ThreadsHandler.h"

#include "../../common/models/events/EventResponseLoginPlayer.h" //Borrar

#include "../Server.h"
#include "../models/User.h"

using namespace std;

class Server;

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        //BlockingQueue <Message*>* receivedMessagesQueue_;
        //unordered_map<IdUser, BlockingQueue<Message *> *> messagesQueues_;

        void createReceivingCycle(User* user);
        void* receivingCycle(User* user);
        void createSendingCycle(User* user);
        void* sendingCycle(User* user);

    public:
        ServerTransmitionManager(Server *server);
        ~ServerTransmitionManager();

        void addUser(User* user);
        BlockingQueue<Message *>* getMessagesToProcess();
};

#endif // _SERVER_TRANSMITION_MANAGER_H_
