#ifndef MESSAGE_GAME_INIT_H_
#define MESSAGE_GAME_INIT_H_

#include "Message.h"
#include "../events/EventGameInit.h"
#include "../events/Event.h"

class MessageGameInit: public Message {

	private:
		screen_t screenSizes_;
		const message_t type_ = GAME_INIT;

    public:
    	explicit MessageGameInit(screen_t screenSizes) : screenSizes_(screenSizes) {}
        Event* deSerialize();
     	responseStatus_t serialize();
        message_t getType();
		screen_t getScreenSizes();
};

#endif