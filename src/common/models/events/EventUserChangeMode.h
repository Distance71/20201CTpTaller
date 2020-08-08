#ifndef EVENT_USER_CHANGE_MODE_H
#define EVENT_USER_CHANGE_MODE_H

#include "Event.h"
#include "../messages/Message.h"
#include "../messages/MessageUserChangeMode.h"

using namespace std;

class EventUserChangeMode: public Event {
    
    public:
        Message* serialize();
        void update();
};

#endif