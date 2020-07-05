#ifndef MESSAGE_USER_MOVEMENT_H_
#define MESSAGE_USER_MOVEMENT_H_

#include "Message.h"
#include "../events/EventUserMovement.h"
#include "../events/Event.h"
#include "../../types.h"

class MessageUserMovement: public Message {
    private:
        orientation_t orientation_;

    public:
        MessageUserMovement(orientation_t orientation): orientation_(orientation) {}
        
        Event* deSerialize();
};

#endif