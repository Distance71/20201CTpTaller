#ifndef MESSAGE_MAP_ELEMENT_CREATE_H_
#define MESSAGE_MAP_ELEMENT_CREATE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMapElementCreate.h"
#include "../events/Event.h"
#include "../../types.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

using namespace std;

class MessageMapElementCreate: public Message {

	private:
		size_t id_;
        char imagePath_[MAX_SIZE_MESSAGE];
        position_t position_;
        spriteSize_t spriteSize_;
        const message_t type_ = MAP_ELEMENT_CREATE;

    public:
    	explicit MessageMapElementCreate(size_t id, char imagePath[MAX_SIZE_MESSAGE], position_t position, spriteSize_t spriteSize) {
            id_ = id;
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++){
                imagePath_[i] = imagePath[i];
            }
            position_ = position;
            spriteSize_ = spriteSize;
        }
        message_t getType();
        Event* deSerialize();
        responseStatus_t serialize();
};

#endif