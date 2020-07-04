#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../events/Event.h"
#include "../../types.h"

class Event;

class Message {

    public:
        virtual Event* deSerialize() = 0;
};

#endif