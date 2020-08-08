#ifndef MESSAGE_USER_CHANGE_MODE_H_
#define MESSAGE_USER_CHANGE_MODE_H_

#include "Message.h"
#include "../events/EventUserChangeMode.h"
#include "../events/Event.h"
#include "../../types.h"

class MessageUserChangeMode: public Message {
    private:
        const message_t type_ = USER_CHANGE_MODE;

    public:
        message_t getType();
        Event* deSerialize();
     	responseStatus_t serialize();
};

#endif