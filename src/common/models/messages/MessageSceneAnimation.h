#ifndef MESSAGE_SCENE_ANIMATION_H_
#define MESSAGE_SCENE_ANIMATION_H_

#include "Message.h"
#include "../events/EventSceneAnimation.h"
#include "../events/Event.h"

class MessageSceneAnimation: public Message {

	private:
        sceneScreen_t scene_;
        const message_t type_ = SCENE_ANIMATION;

    public:
    	explicit MessageSceneAnimation(sceneScreen_t scene) :scene_(scene){}
        message_t getType();
        Event* deSerialize();
        sceneScreen_t getScene();
        responseStatus_t serialize();
};

#endif