#ifndef MESSAGE_MAP_ELEMENT_UPDATE_H_
#define MESSAGE_MAP_ELEMENT_UPDATE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMapElementUpdate.h"
#include "../events/Event.h"
#include "../../types.h"

#define MAX_SIZE 100

using namespace std;

class MessageMapElementUpdate: public Message {

	private:
		size_t id_;
        position_t position_;

    public:
    	explicit MessageMapElementUpdate(size_t id, position_t position): id_(id), position_(position) {}

        Event* deSerialize();
};

#endif