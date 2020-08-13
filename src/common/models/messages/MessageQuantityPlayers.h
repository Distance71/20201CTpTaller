#ifndef MESSAGE_QUANTITY_PLAYERS_H_
#define MESSAGE_QUANTITY_PLAYERS_H_

#include "Message.h"
#include "../events/EventQuantityPlayers.h"
#include "../events/Event.h"

class MessageQuantityPlayers: public Message {

	private:
        unsigned int quantityPlayers_;
        const message_t type_ = QUANTITY_PLAYERS;

    public:
    	explicit MessageQuantityPlayers(unsigned int quantityPlayers) : quantityPlayers_(quantityPlayers){}
        message_t getType();
        Event* deSerialize();
        unsigned int getQuantityPlayers();
        responseStatus_t serialize();
};

#endif