#ifndef EVENT_ANIMATION_INIT_STAGE_H_
#define EVENT_ANIMATION_INIT_STAGE_H_

#include "Event.h"
#include "../messages/MessageSceneAnimation.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

using namespace std;

class EventSceneAnimation: public Event {

	private:
        sceneScreen_t scene_;

    public:
        EventSceneAnimation(sceneScreen_t scene) : scene_(scene){}
        
        Message* serialize();
        void update();
};

#endif