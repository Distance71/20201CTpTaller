#ifndef MESSAGE_ANIMATION_INIT_STAGE_H_
#define MESSAGE_ANIMATION_INIT_STAGE_H_

#include "Message.h"
#include "../events/EventAnimationInitStage.h"
#include "../events/Event.h"
#include "../../../client/Client.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

class MessageAnimationInitStage: public Message {

	private:
        sceneScreen_t scene_;
        const message_t type_ = ANIMATION_INIT_STAGE;

    public:
    	explicit MessageAnimationInitStage(sceneScreen_t scene) :scene_(scene){}
        message_t getType();
        Event* deSerialize();
        responseStatus_t serialize();
        sceneScreen_t getScene();
};

#endif