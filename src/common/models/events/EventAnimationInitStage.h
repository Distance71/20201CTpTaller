#ifndef EVENT_ANIMATION_INIT_STAGE_H_
#define EVENT_ANIMATION_INIT_STAGE_H_

#include "Event.h"
#include "../messages/MessageAnimationInitStage.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventAnimationInitStage: public Event {

	private:
        sceneScreen_t scene_;

    public:
        EventAnimationInitStage(sceneScreen_t scene) : scene_(scene){}
        
        Message* serialize();
        void update();
};

#endif