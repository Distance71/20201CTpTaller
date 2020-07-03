#ifndef MESSAGE_USER_LOGIN_H_
#define MESSAGE_USER_LOGIN_H_

#include "../events/EventGameInit.h"
#include "../events/Event.h"
#include "Message.h"

class MessageUserLogin: public Message {

    public:
        MessageUserLogin();
        
        Event* deSerialize();
};

#endif