#ifndef EVENT_INIT_STAGE_H_
#define EVENT_INIT_STAGE_H_

#include "Event.h"
#include "../messages/MessageInitStage.h"
#include "../messages/Message.h"
#include "../../types.h"
#include "../../../client/Client.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

#define QUANTITY_LAYERS 7

using namespace std;

class EventInitStage: public Event {
    private:
		char layerPaths_[QUANTITY_LAYERS][MAX_SIZE_MESSAGE];

    public:
        explicit EventInitStage(char layerPaths[QUANTITY_LAYERS][MAX_SIZE_MESSAGE]) {
            for(size_t i = 0; i < QUANTITY_LAYERS; i++){
                for(size_t j = 0; j < MAX_SIZE_MESSAGE; j++)
                    layerPaths_[i][j] = layerPaths[i][j];
            }
        }
        Message* serialize();
        void update();
};

#endif