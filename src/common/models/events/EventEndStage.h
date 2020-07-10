#ifndef EVENT_END_STAGE_H_
#define EVENT_END_STAGE_H_

#include "Event.h"
#include "../messages/MessageEndStage.h"
#include "../messages/Message.h"
#include "../../../client/Client.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif 

using namespace std;

class EventEndStage: public Event {
    
    private:
        char path_[MAX_SIZE_MESSAGE];

    public:
        EventEndStage(char path[MAX_SIZE_MESSAGE]) {
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++)
                path_[i] = path[i];
        }
        Message* serialize();
        void update();
};

#endif