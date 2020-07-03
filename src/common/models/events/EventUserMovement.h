#ifndef EVENT_USER_MOVEMENT_H
#define EVENT_USER_MOVEMENT_H

#include "Event.h"
#include "../../types.h"
#include "Message.h"
#include "MessageUserMovement.h"

class EventUserMovement: public Event {

    private:
        orientation_t orientation_; //Consider a default value

    public:
        EventUserMovement(orientation_t orientation);
        
        Message* serialize() override;
        void update() override;
};

#endif