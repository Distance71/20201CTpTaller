#ifndef MESSAGE_MAP_ELEMENT_CREATE_H_
#define MESSAGE_MAP_ELEMENT_CREATE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventMapElementCreate.h"
#include "../events/Event.h"
#include "../../types.h"

#define MAX_SIZE 100

using namespace std;

class MessageMapElementCreate: public Message {

	private:
		size_t id_;
        char imagePath_[MAX_SIZE];
        position_t position_;
        spriteSize_t spriteSize_;

    public:
    	explicit MessageMapElementCreate(size_t id, char imagePath[MAX_SIZE], position_t position, spriteSize_t spriteSize) {
            id_ = id;
            for(size_t i = 0; i < MAX_SIZE; i++){
                imagePath_[i] = imagePath[i];
            }
            position_ = position;
            spriteSize_ = spriteSize;
        }

        Event* deSerialize();
};

#endif