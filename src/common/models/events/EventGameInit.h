#ifndef EVENT_GAME_INIT_H
#define EVENT_GAME_INIT_H

#include "Event.h"
#include "../messages/MessageGameInit.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"

class Event;

class EventGameInit: public Event {

	private:
        size_t width_;
        size_t height_;

    public:
        explicit EventGameInit(size_t width, size_t height);
        
        Message* serialize() override;
        void update() override;
};

#endif