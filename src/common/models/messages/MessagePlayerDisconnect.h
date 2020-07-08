#ifndef MESSAGE_PLAYER_DISCONNECT_H_
#define MESSAGE_PLAYER_DISCONNECT_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventPlayerDisconnect.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessagePlayerDisconnect: public Message {

	private:
		size_t id_;
		const message_t type_ = PLAYER_DISCONNECT;

    public:
    	explicit MessagePlayerDisconnect(size_t id): id_(id) {}
    	message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize() {};
};

#endif