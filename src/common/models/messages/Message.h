#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../events/Event.h"

class Event;

class Message {

    public:
        Message() = default;
        message_t type_;

        virtual Event* deSerialize();
};

#endif