#ifndef MESSAGE_ANIMATION_INIT_STAGE_H_
#define MESSAGE_ANIMATION_INIT_STAGE_H_

#include "Message.h"
#include "../events/EventAnimationInitStage.h"
#include "../events/Event.h"
#include "../../../client/Client.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

class MessageAnimationInitStage: public Message {

	private:
        char path_[MAX_SIZE_MESSAGE];
        const message_t type_ = ANIMATION_INIT_STAGE;

    public:
    	explicit MessageAnimationInitStage(char path[MAX_SIZE_MESSAGE]) {
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++)
                path_[i] = path[i];
        }
        message_t getType();
        Event* deSerialize();
        responseStatus_t serialize();
        char* getPath();
};

#endif