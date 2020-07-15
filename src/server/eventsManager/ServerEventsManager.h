#ifndef _SERVEREVENTSMANAGER_H_
#define _SERVEREVENTSMANAGER_H_

#include "../../common/models/BlockingQueue.h"
#include "../../common/models/messages/Message.h"
#include "../Server.h"
#include "../../common/models/events/Event.h"

class Server;

class ServerEventsManager {
   
    private:
        Server *serverOwn_;
        BlockingQueue<Event*>* eventsQueue_;
    
    public:
        
        ServerEventsManager(Server *server);
        ~ServerEventsManager();

        void processEvent(Event *event);
        Event* getEvent();
        Server* getServer();
        void RunProcessEventsThread();
};

#endif