#ifndef MESSAGE_INIT_STAGE_H_
#define MESSAGE_INIT_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventInitStage.h"
#include "../events/Event.h"

#define MAX_SIZE 100
#define QUANTITY_LAYERS 7

using namespace std;

class MessageInitStage: public Message {

	private:
		char layerPaths_[QUANTITY_LAYERS][MAX_SIZE];

    public:
    	explicit MessageInitStage(char layerPaths[QUANTITY_LAYERS][MAX_SIZE]) {
            for(size_t i = 0; i < QUANTITY_LAYERS; i++){
                for(size_t j = 0; j < MAX_SIZE; j++)
                    layerPaths_[i][j] = layerPaths[i][j];
            }
        }

        Event* deSerialize();
};

#endif