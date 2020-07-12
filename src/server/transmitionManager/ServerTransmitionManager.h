#ifndef _SERVER_TRANSMITION_MANAGER_H_
#define _SERVER_TRANSMITION_MANAGER_H_

#include <errno.h>
#include <thread>
#include <chrono>

#include "../../common/models/Socket.h"
#include "../../common/types.h"
#include "../../common/models/messages/Message.h"
#include "../../common/models/BlockingQueue.h"
//#include "../../common/models/BlockingMap.h"
#include "../../common/services/ThreadsHandler.h"
#include <SDL2/SDL.h>

#include "../Server.h"
#include "../models/User.h"

//Borrar
#include "../../common/models/events/EventResponseLoginPlayer.h"
#include "../../common/models/events/EventEndStage.h"

using namespace std;

class Server;

class ServerTransmitionManager {
    private:
        Server *serverOwn_;
        std::mutex mtxErrno;
        BlockingQueue <Event*>* receivedEventQueue_;
        //BlockingMap<Id, BlockingQueue<Message *> *> messagesQueues_;

        void createReceivingCycle(User* user);
        void* receivingCycle(User* user);
        void createSendingCycle(User* user);
        void* sendingCycle(User* user);

    public:
        ServerTransmitionManager(Server *server);
        ~ServerTransmitionManager();

        void addUser(User* user);
        void sendToUser(Id idUser);
        void sendToAllUsers(Event *event);
        BlockingQueue<Message *>* getMessagesToProcess();
};

#endif // _SERVER_TRANSMITION_MANAGER_H_
