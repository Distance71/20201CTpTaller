#ifndef EVENT_H
#define EVENT_H

#include "../../models/messages/Message.h"

class Message;

class Event {

    public:
        Event() = default;
        ~Event() = default;

    virtual Message* serialize();
    virtual void update(); //Just for understanding better. Should be naming execute
    
};

#endif