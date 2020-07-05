#ifndef MESSAGE_PLAYER_RECONNECT_H_
#define MESSAGE_PLAYER_RECONNECT_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventPlayerReconnect.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessagePlayerReconnect: public Message {

	private:
		size_t id_;

    public:
    	explicit MessagePlayerReconnect(size_t id): id_(id) {}

        Event* deSerialize();
};

#endif