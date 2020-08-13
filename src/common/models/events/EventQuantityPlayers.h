#ifndef EVENT_QUANTITY_PLAYERS_H_
#define EVENT_QUANTITY_PLAYERS_H_

#include <iostream>
#include <string.h>
#include "../messages/Message.h"
#include "../messages/MessageQuantityPlayers.h"
#include "../events/Event.h"
#include "../../types.h"
#include "../../../client/Client.h"

using namespace std;

class EventQuantityPlayers: public Event {

	private:
        unsigned int quantityPlayers_;

    public:
    	EventQuantityPlayers(unsigned int quantityPlayers) : quantityPlayers_(quantityPlayers) {}

        Message* serialize();
        void update();
};

#endif