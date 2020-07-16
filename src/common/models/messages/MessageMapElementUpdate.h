#ifndef MESSAGE_MAP_ELEMENT_UPDATE_H_
#define MESSAGE_MAP_ELEMENT_UPDATE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMapElementUpdate.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessageMapElementUpdate: public Message {

	private:
		elementType_t elementType_;
        position_t position_;
        const message_t type_ = MAP_ELEMENT_UPDATE;

    public:
    	explicit MessageMapElementUpdate(elementType_t elementType, position_t position): elementType_(elementType), position_(position) {}
    	message_t getType();
        Event* deSerialize();

        elementType_t getElementType();
        position_t getPosition();
};

#endif