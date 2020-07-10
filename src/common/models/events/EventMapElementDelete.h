#ifndef EVENT_MAP_ELEMENT_DELETE_H_
#define EVENT_MAP_ELEMENT_DELETE_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessageMapElementDelete.h"
#include "../events/Event.h"
#include "../../types.h"


using namespace std;

class EventMapElementDelete: public Event {

	private:
		size_t id_;

    public:
    	explicit EventMapElementDelete(size_t id): id_(id) {}

        Message* serialize();
        void update();
};

#endif