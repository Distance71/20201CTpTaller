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
        sceneScreen_t scene_;

    public:
        EventEndStage(sceneScreen_t scene) : scene_(scene){}
        Message* serialize();
        void update();
};

#endif