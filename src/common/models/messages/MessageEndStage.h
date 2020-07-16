#ifndef MESSAGE_END_STAGE_H_
#define MESSAGE_END_STAGE_H_

#include <iostream>
#include <string.h>
#include "Message.h"
#include "../events/EventEndStage.h"
#include "../events/Event.h"

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

using namespace std;

class MessageEndStage: public Message {

	private:
		sceneScreen_t scene_;
		const message_t type_ = END_STAGE;

    public:
    	explicit MessageEndStage(sceneScreen_t scene) : scene_(scene){}
        message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize();
        sceneScreen_t getScene();
};

#endif