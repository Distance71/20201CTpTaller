#ifndef MESSAGE_USER_SHOOT_H_
#define MESSAGE_USER_SHOOT_H_

#include "Message.h"
#include "../events/EventUserShoot.h"
#include "../events/Event.h"
#include "../../types.h"

class MessageUserShoot: public Message {
    private:
        const message_t type_ = USER_SHOOT;

    public:
        message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize();
};

#endif