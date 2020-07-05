#ifndef EVENT_INIT_STAGE_H_
#define EVENT_INIT_STAGE_H_

#include "Event.h"
#include "../messages/MessageInitStage.h"
#include "../messages/Message.h"

#define MAX_SIZE 100
#define QUANTITY_LAYERS 7

using namespace std;

class EventInitStage: public Event {
    private:
		char layerPaths_[QUANTITY_LAYERS][MAX_SIZE];

    public:
        explicit EventInitStage(char layerPaths[QUANTITY_LAYERS][MAX_SIZE]) {
            for(size_t i = 0; i < QUANTITY_LAYERS; i++){
                for(size_t j = 0; j < MAX_SIZE; j++)
                    layerPaths_[i][j] = layerPaths[i][j];
            }
        }
        Message* serialize();
        void update();
};

#endif