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
		size_t id_;
        position_t position_;

    public:
    	explicit EventMapElementUpdate(size_t id, position_t position): id_(id), position_(position) {}

        Message* serialize();
        void update();
};

#endif