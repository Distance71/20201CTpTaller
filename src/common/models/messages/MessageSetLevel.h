#ifndef MESSAGE_SET_LEVEL
#define MESSAGE_SET_LEVEL

#include "Message.h"
#include "../events/EventSetLevel.h"
#include "../events/Event.h"

class MessageSetLevel: public Message {

	private:
        level_t level_;
        const message_t type_ = SET_LEVEL;

    public:
    	explicit MessageSetLevel(level_t level) :level_(level){}
        message_t getType();
        Event* deSerialize();
        level_t getLevel();
        responseStatus_t serialize();
};

#endif