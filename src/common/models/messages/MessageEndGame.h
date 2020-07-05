#ifndef MESSAGE_END_GAME_H_
#define MESSAGE_END_GAME_H_

#include "Message.h"
#include "../events/EventEndGame.h"
#include "../events/Event.h"

class MessageEndGame: public Message {
    public:
        Event* deSerialize();
};

#endif