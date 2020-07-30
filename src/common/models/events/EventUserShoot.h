#ifndef EVENT_USER_SHOOT_H
#define EVENT_USER_SHOOT_H

#include "Event.h"
#include "../messages/Message.h"
#include "../messages/MessageUserShoot.h"

using namespace std;

class EventUserShoot: public Event {
    
    public:
        Message* serialize();
        void update();
};

#endif