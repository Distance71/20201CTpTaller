#ifndef EVENT_USER_MOVEMENT_H
#define EVENT_USER_MOVEMENT_H

#include "Event.h"
#include "../../types.h"
#include "../messages/Message.h"
#include "../messages/MessageUserMovement.h"

using namespace std;

class EventUserMovement: public Event {

    private:
        orientation_t orientation_; //Consider a default value

    public:
        EventUserMovement(orientation_t orientation): orientation_(orientation) {};
        
        Message* serialize();
        void update();
};

#endif