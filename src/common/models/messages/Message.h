#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "../events/Event.h"

class Event;

class Message {

    public:
        Message() = default;

        virtual Event* deSerialize();
};

#endif