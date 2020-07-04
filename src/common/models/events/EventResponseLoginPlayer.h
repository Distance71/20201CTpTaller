/*#ifndef EVENT_RESPONSE_LOGIN_PLAYER
#define EVENT_RESPONSE_LOGIN_PLAYER

#include "Event.h"
#include "../../types.h"
#include "../messages/Message.h"

class EventResponseLoginPlayer: public Event{
    private:
        loginAnswer_t answer_;

    public:
        explicit EventResponseLoginPlayer(loginAnswer_t answer_);
        void update() override;
        Message* serialize() override;
};

#endif*/