#ifndef EVENT_PLAYER_DISCONNECT_H_
#define EVENT_PLAYER_DISCONNECT_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../events/Event.h"
#include "../../types.h"
#include "../../../client/Client.h"


using namespace std;

class EventPlayerDisconnect: public Event {

	private:
		size_t id_;

    public:
    	explicit EventPlayerDisconnect(size_t id): id_(id) {}

        Message* serialize();
        void update();
};

#endif