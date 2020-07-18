#ifndef MESSAGE_SET_STAGE
#define MESSAGE_SET_STAGE

#include "Message.h"
#include "../events/EventSetStage.h"
#include "../events/Event.h"

class MessageSetStage: public Message {

	private:
        stage_t stage_;
        const message_t type_ = SET_STAGE;

    public:
    	explicit MessageSetStage(stage_t stage) :stage_(stage){}
        message_t getType();
        Event* deSerialize();
        stage_t getStage();
        responseStatus_t serialize();
};

#endif
