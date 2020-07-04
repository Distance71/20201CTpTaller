#ifndef MESSAGE_GAME_INIT_H_
#define MESSAGE_GAME_INIT_H_

#include "Message.h"
#include "../events/EventGameInit.h"
#include "../events/Event.h"

class MessageGameInit: public Message {

	private:
		size_t width_;
        size_t height_;

    public:
    	explicit MessageGameInit(size_t width, size_t height) : width_(width), height_(height) {}
        Event* deSerialize();
};

#endif