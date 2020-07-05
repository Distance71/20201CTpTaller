#ifndef MESSAGE_RESPONSE_LOGIN_PLAYER_H_
#define MESSAGE_RESPONSE_LOGIN_PLAYER_H_

#include "Message.h"
#include "../events/EventResponseLoginPlayer.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessageResponseLoginPlayer: public Message {

	private:
        responseStatus_t response_;

    public:
    	explicit MessageResponseLoginPlayer(responseStatus_t response) : response_(response) {}
        Event* deSerialize();
};

#endif