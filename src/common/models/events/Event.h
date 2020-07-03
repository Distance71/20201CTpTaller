#ifndef EVENT_H
#define EVENT_H

#include "../../models/messages/Message.h"
#include "../../../client/Client.h"
#include "../../../server/Server.h"

class Client;

using namespace std;

class Event {

    public:
        Event();
        ~Event();
        void setClientContext(Client* client_);
        void setServerContext(Server* server_);

        virtual Message* serialize();
        virtual void update(); //Just for understanding better. Should be naming execute

    protected:
        Client* client;
        Server* server;
};

#endif