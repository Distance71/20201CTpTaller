#ifndef EVENT_GAME_OVER_H_
#define EVENT_GAME_OVER_H_

#include "Event.h"
#include "../messages/MessageGameOver.h"
#include "../messages/Message.h"
#include "../../../client/Client.h"

using namespace std;

class EventGameOver: public Event {
    public:
        Message* serialize();
        void update();
};

#endif