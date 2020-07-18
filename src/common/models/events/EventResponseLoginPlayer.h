#ifndef EVENT_RESPONSE_LOGIN_PLAYER
#define EVENT_RESPONSE_LOGIN_PLAYER

#include "Event.h"
#include "../../types.h"
#include "../messages/Message.h"
#include "../messages/MessageResponseLoginPlayer.h"
#include "../../../client/Client.h"

class EventResponseLoginPlayer: public Event{
    private:
        responseStatus_t response_;

    public:
        explicit EventResponseLoginPlayer(responseStatus_t response): response_(response) {};
        Message* serialize();
        void update();

};

#endif