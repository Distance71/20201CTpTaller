#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"

class EventGameInit: public Event {

    public:
        EventGameInit() = default;
        ~EventGameInit() = default;
        
        Message* serialize() override;
        void update() override;
};

#endif