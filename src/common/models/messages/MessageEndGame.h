#ifndef MESSAGE_END_GAME_H_
#define MESSAGE_END_GAME_H_

#include "Message.h"
#include "../events/EventEndGame.h"
#include "../events/Event.h"

class MessageEndGame: public Message {

	private:
		const message_t type_ = END_GAME;

    public:
        Event* deSerialize();
        message_t getType();
        responseStatus_t serialize() override;
};

#endif