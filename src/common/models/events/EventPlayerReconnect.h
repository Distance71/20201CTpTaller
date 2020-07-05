#ifndef EVENT_PLAYER_RECONNECT_H_
#define EVENT_PLAYER_RECONNECT_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessagePlayerReconnect.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class EventPlayerReconnect: public Event {

	private:
		size_t id_;

    public:
    	explicit EventPlayerReconnect(size_t id): id_(id) {}

        Message* serialize();
        void update();
};

#endif