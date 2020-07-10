#ifndef MESSAGE_END_STAGE_H_
#define MESSAGE_END_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventEndStage.h"
#include "../events/Event.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

using namespace std;

class MessageEndStage: public Message {

	private:
		char path_[MAX_SIZE_MESSAGE];
		const message_t type_ = END_STAGE;

    public:
    	explicit MessageEndStage(char path[MAX_SIZE_MESSAGE]) {
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++){
                path_[i] = path[i];
            }
        }
        message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize();
};

#endif