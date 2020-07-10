#ifndef MESSAGE_MAP_ELEMENT_DELETE_H_
#define MESSAGE_MAP_ELEMENT_DELETE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMapElementDelete.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessageMapElementDelete: public Message {

	private:
		size_t id_;
		const message_t type_ = MAP_ELEMENT_DELETE;

    public:
    	explicit MessageMapElementDelete(size_t id): id_(id) {}
    	message_t getType();
        Event* deSerialize();
        responseStatus_t serialize();
};

#endif