#ifndef MESSAGE_ANIMATION_INIT_STAGE_H_
#define MESSAGE_ANIMATION_INIT_STAGE_H_

#include "Message.h"
#include "../events/EventAnimationInitStage.h"
#include "../events/Event.h"

#define MAX_SIZE 100

class MessageAnimationInitStage: public Message {

	private:
        char path_[MAX_SIZE];

    public:
    	explicit MessageAnimationInitStage(char path[MAX_SIZE]) {
            for(size_t i = 0; i < MAX_SIZE; i++)
                path_[i] = path[i];
        }

        Event* deSerialize();
};

#endif