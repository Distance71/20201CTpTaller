#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"
#include "../messages/MessageGameInit.h"
#include "../messages/Message.h"

class EventGameInit: public Event {

    public:
        EventGameInit() = default;
        
        Message* serialize() override;
        void update() override;
};

#endif