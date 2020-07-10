#ifndef MESSAGE_INIT_STAGE_H_
#define MESSAGE_INIT_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventInitStage.h"
#include "../events/Event.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif
#define QUANTITY_LAYERS 7

using namespace std;

class MessageInitStage: public Message {

	private:
		char layerPaths_[QUANTITY_LAYERS][MAX_SIZE_MESSAGE];
        const message_t type_ = INIT_STAGE;

    public:
    	explicit MessageInitStage(char layerPaths[QUANTITY_LAYERS][MAX_SIZE_MESSAGE]) {
            for(size_t i = 0; i < QUANTITY_LAYERS; i++){
                for(size_t j = 0; j < MAX_SIZE_MESSAGE; j++)
                    layerPaths_[i][j] = layerPaths[i][j];
            }
        }
        message_t getType();
        Event* deSerialize();
        responseStatus_t serialize();

};

#endif