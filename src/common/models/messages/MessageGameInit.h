#ifndef MESSAGE_GAME_INIT_H_
#define MESSAGE_GAME_INIT_H_

#include "../events/EventGameInit.h"
#include "Message.h"
#include "../events/Event.h"

class MessageGameInit: public Message {

    public:
        MessageGameInit() = default;
        
        Event* deSerialize();
};

#endif