#ifndef EVENT_ANIMATION_INIT_STAGE_H_
#define EVENT_ANIMATION_INIT_STAGE_H_

#include "Event.h"
#include "../messages/MessageAnimationInitStage.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"

#define MAX_SIZE 100

using namespace std;

class EventAnimationInitStage: public Event {

	private:
        char path_[MAX_SIZE];

    public:
        EventAnimationInitStage(char path[MAX_SIZE]) {
            for(size_t i = 0; i < MAX_SIZE; i++)
                path_[i] = path[i];
        }
        
        Message* serialize();
        void update();
};

#endif