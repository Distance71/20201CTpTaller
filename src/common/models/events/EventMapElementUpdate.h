#ifndef EVENT_MAP_ELEMENT_UPDATE_H_
#define EVENT_MAP_ELEMENT_UPDATE_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessageMapElementUpdate.h"
#include "../events/Event.h"
#include "../../types.h"
#include "../../../client/Client.h"

using namespace std;

class EventMapElementUpdate: public Event {

	private:
		elementType_t type_;
        position_t position_;

    public:
    	EventMapElementUpdate(elementType_t type, position_t position): type_(type), position_(position) {}

        Message* serialize();
        void update();
};

#endif