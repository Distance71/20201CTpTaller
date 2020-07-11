#ifndef MESSAGE_USER_MOVEMENT_H_
#define MESSAGE_USER_MOVEMENT_H_

#include "Message.h"
#include "../events/EventUserMovement.h"
#include "../events/Event.h"
#include "../../types.h"

class MessageUserMovement: public Message {
    private:
        orientation_t orientation_;
        const message_t type_ = USER_MOVEMENT;

    public:
        MessageUserMovement(orientation_t orientation): orientation_(orientation) {}
        message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize();
        orientation_t getOrientation();
};

#endif