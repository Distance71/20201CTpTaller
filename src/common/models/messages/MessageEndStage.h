#ifndef MESSAGE_END_STAGE_H_
#define MESSAGE_END_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventEndStage.h"
#include "../events/Event.h"

#define MAX_SIZE 100

using namespace std;

class MessageEndStage: public Message {

	private:
		char path_[MAX_SIZE];

    public:
    	explicit MessageEndStage(char path[MAX_SIZE]) {
            for(size_t i = 0; i < MAX_SIZE; i++){
                path_[i] = path[i];
            }
        }

        Event* deSerialize();
};

#endif