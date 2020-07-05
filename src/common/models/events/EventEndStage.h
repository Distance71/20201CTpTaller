#ifndef EVENT_END_STAGE_H_
#define EVENT_END_STAGE_H_

#include "Event.h"
#include "../messages/MessageEndStage.h"
#include "../messages/Message.h"

#define MAX_SIZE 100 

using namespace std;

class EventEndStage: public Event {
    
    private:
        char path_[MAX_SIZE];

    public:
        EventEndStage(char path[MAX_SIZE]) {
            for(size_t i = 0; i < MAX_SIZE; i++)
                path_[i] = path[i];
        }
        Message* serialize();
        void update();
};

#endif