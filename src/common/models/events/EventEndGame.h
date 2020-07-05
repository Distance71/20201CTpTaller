#ifndef EVENT_END_GAME_H_
#define EVENT_END_GAME_H_

#include "Event.h"
#include "../messages/MessageEndGame.h"
#include "../messages/Message.h"

using namespace std;

class EventEndGame: public Event {
    public:
        Message* serialize();
        void update();
};

#endif