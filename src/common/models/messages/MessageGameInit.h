#ifndef MESSAGE_GAME_INIT_H_
#define MESSAGE_GAME_INIT_H_

#include "../events/EventGameInit.h"
#include "Message.h"
#include "../events/Event.h"

class Message;

class MessageGameInit: public Message {

	private:
		size_t width_;
        size_t height_;

    public:
    	MessageGameInit(size_t width, size_t height);
        Event* deSerialize() override;
};

#endif