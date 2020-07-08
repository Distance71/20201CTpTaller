#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../events/Event.h"
#include "../../types.h"

class Event;

class Message {

    public:
        virtual Event* deSerialize() = 0;
        virtual message_t getType() = 0;
};

#endif