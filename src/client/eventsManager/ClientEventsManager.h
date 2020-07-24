#ifndef _CLIENTEVENTSMANAGER_H_
#define _CLIENTEVENTSMANAGER_H_

#include <netinet/in.h>
#include <arpa/inet.h>
#include "../Client.h"
#include "../../common/types.h"
#include "../../common/models/events/Event.h"
#include "../../common/models/BlockingQueue.h"
#include"../../common/models/messages/MessageUserMovement.h"

class Client;

class ClientEventsManager {
    
    private:
        BlockingQueue<Event *>* eventsQueue_;
        Client *clientOwn_;
        bool stop_;
        bool logged; 

    public:
        ClientEventsManager(Client* client);
        ~ClientEventsManager();
        void pushBackEvent(Event* event);
        Event* getEvent();
        void RunDetectPlayerEventsThread();
        void RunProcessEventsThread();
        Client* getClient();
};

#endif