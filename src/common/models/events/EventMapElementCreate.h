#ifndef EVENT_MAP_ELEMENT_CREATE_H_
#define EVENT_MAP_ELEMENT_CREATE_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessageMapElementCreate.h"
#include "../events/Event.h"
#include "../../types.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

using namespace std;

class EventMapElementCreate: public Event {

	private:
		size_t id_;
        char imagePath_[MAX_SIZE_MESSAGE];
        position_t position_;
        spriteSize_t spriteSize_;

    public:
    	explicit EventMapElementCreate(size_t id, char imagePath[MAX_SIZE_MESSAGE], position_t position, spriteSize_t spriteSize) {
            id_ = id;
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++)
                imagePath_[i] = imagePath[i];
            
            position_ = position;
            spriteSize_ = spriteSize;
        }

        Message* serialize();
        void update();
};

#endif