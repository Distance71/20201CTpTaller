#ifndef MESSAGE_GAME_OVER_H_
#define MESSAGE_GAME_OVER_H_

#include "Message.h"
#include "../events/EventGameOver.h"
#include "../events/Event.h"

class MessageGameOver: public Message {

	private:
		const message_t type_ = GAME_OVER;

  public:
      Event* deSerialize();
      message_t getType();
      responseStatus_t serialize();
};

#endif